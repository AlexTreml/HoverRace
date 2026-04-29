// AudioAnalysisMaster.cpp — submix listener + Goertzel frequency analysis driving Bass/Mids/Treble outputs.

#include "AudioAnalysisMaster.h"

#include "AudioDevice.h"
#include "AudioDeviceManager.h"
#include "ISubmixBufferListener.h"
#include "Sound/SoundSubmix.h"

/**
 * @brief ISubmixBufferListener implementation that forwards audio thread buffers
 *        to the owning AAudioAnalysisMaster actor.
 */
class FSubmixListenerHelper : public ISubmixBufferListener
{
public:
	AAudioAnalysisMaster* Owner = nullptr;

	FSubmixListenerHelper(AAudioAnalysisMaster* InOwner)
		: Owner(InOwner)
	{
	}

	/** @brief Audio-thread callback — copy buffer into the owning actor's capture slot. */
	virtual void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override
	{
		if (Owner)
		{
			Owner->HandleNewSubmixBuffer(AudioData, NumSamples, NumChannels, SampleRate);
		}
	}
};

/** @brief Enable Tick on the actor. */
AAudioAnalysisMaster::AAudioAnalysisMaster()
{
	PrimaryActorTick.bCanEverTick = true;
}

/** @brief Create the submix listener and register it with the audio device. */
void AAudioAnalysisMaster::BeginPlay()
{
	Super::BeginPlay();

	SubmixListener = MakeShared<FSubmixListenerHelper, ESPMode::ThreadSafe>(this);

	if (FAudioDevice* AudioDevice = GetWorld()->GetAudioDeviceRaw())
	{
		// Submix required by new 5.4+ API — fall back to the device's main output submix if none set.
		USoundSubmix& TargetSubmix = Submix ? *Submix : AudioDevice->GetMainSubmixObject();
		AudioDevice->RegisterSubmixBufferListener(SubmixListener.ToSharedRef(), TargetSubmix);
		UE_LOG(LogTemp, Log, TEXT("AudioAnalysisMaster: Registered submix listener (Submix: %s)"),
			*TargetSubmix.GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioAnalysisMaster: No audio device available."));
	}
}

/** @brief Unregister the submix listener and clear the back-pointer. */
void AAudioAnalysisMaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (SubmixListener.IsValid())
	{
		if (FAudioDevice* AudioDevice = GetWorld()->GetAudioDeviceRaw())
		{
			USoundSubmix& TargetSubmix = Submix ? *Submix : AudioDevice->GetMainSubmixObject();
			AudioDevice->UnregisterSubmixBufferListener(SubmixListener.ToSharedRef(), TargetSubmix);
		}

		// Clear the back-pointer so the audio thread doesn't call into a destroyed actor.
		SubmixListener->Owner = nullptr;
		SubmixListener.Reset();
	}

	Super::EndPlay(EndPlayReason);
}

/**
 * @brief Audio-thread receiver: down-mix to mono and store under a critical section
 *        for the game thread to consume in Tick.
 */
void AAudioAnalysisMaster::HandleNewSubmixBuffer(float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate)
{
	if (NumSamples <= 0 || NumChannels <= 0)
	{
		return;
	}

	// Down-mix to mono by averaging channels.
	const int32 NumFrames = NumSamples / NumChannels;

	FScopeLock Lock(&BufferCriticalSection);
	CapturedBuffer.SetNumUninitialized(NumFrames);

	for (int32 Frame = 0; Frame < NumFrames; Frame++)
	{
		float Sum = 0.0f;
		for (int32 Ch = 0; Ch < NumChannels; Ch++)
		{
			Sum += AudioData[Frame * NumChannels + Ch];
		}
		CapturedBuffer[Frame] = Sum / NumChannels;
	}

	CapturedSampleRate = SampleRate;
	bHasNewData = true;
}

/**
 * @brief Per-frame analysis: read the captured buffer, compute RMS amplitude and
 *        per-band Goertzel magnitudes, smooth, and produce normalised outputs.
 */
void AAudioAnalysisMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Take the latest captured buffer from the audio thread.
	TArray<float> AnalysisBuffer;
	int32 SampleRate = 0;

	{
		FScopeLock Lock(&BufferCriticalSection);
		if (!bHasNewData || CapturedBuffer.Num() == 0)
		{
			return;
		}
		AnalysisBuffer = CapturedBuffer;
		SampleRate = CapturedSampleRate;
		bHasNewData = false;
	}

	// ========== AMPLITUDE (RMS) ==========
	float RMS = 0.0f;
	for (const float Sample : AnalysisBuffer)
	{
		RMS += Sample * Sample;
	}
	RMS = FMath::Sqrt(RMS / AnalysisBuffer.Num());
	const float TargetAmplitude = RMS * AmplitudeGain;

	// ========== FREQUENCY BANDS (Goertzel) ==========
	// Sample several frequencies per band and average the magnitudes.

	// Bass: 5 sample points across 40-250 Hz
	const float BassFreqs[] = { 40.0f, 80.0f, 120.0f, 180.0f, 250.0f };
	float TargetBass = 0.0f;
	for (float Freq : BassFreqs)
	{
		TargetBass += GetMagnitudeAtFrequency(AnalysisBuffer, SampleRate, Freq);
	}
	TargetBass /= UE_ARRAY_COUNT(BassFreqs);

	// Mids: 5 sample points across 500-4000 Hz
	const float MidsFreqs[] = { 500.0f, 1000.0f, 2000.0f, 3000.0f, 4000.0f };
	float TargetMids = 0.0f;
	for (float Freq : MidsFreqs)
	{
		TargetMids += GetMagnitudeAtFrequency(AnalysisBuffer, SampleRate, Freq);
	}
	TargetMids /= UE_ARRAY_COUNT(MidsFreqs);

	// Treble: 4 sample points across 6000-16000 Hz
	const float TrebleFreqs[] = { 6000.0f, 10000.0f, 14000.0f, 16000.0f };
	float TargetTreble = 0.0f;
	for (float Freq : TrebleFreqs)
	{
		TargetTreble += GetMagnitudeAtFrequency(AnalysisBuffer, SampleRate, Freq);
	}
	TargetTreble /= UE_ARRAY_COUNT(TrebleFreqs);

	// Apply gain
	TargetBass *= BassGain;
	TargetMids *= MidsGain;
	TargetTreble *= TrebleGain;

	// ========== SMOOTH VALUES ==========
	Bass = SmoothValue(Bass, TargetBass, DeltaTime);
	Mids = SmoothValue(Mids, TargetMids, DeltaTime);
	Treble = SmoothValue(Treble, TargetTreble, DeltaTime);
	Amplitude = SmoothValue(Amplitude, TargetAmplitude, DeltaTime);

	// Normalised 0-0.85 using tanh curve for smooth compression.
	// tanh(x) naturally saturates — values approach but never reach 1.0.
	// Multiplied by 0.85 so even the loudest peaks stay below white-out.
	auto TanhNorm = [](float Value) -> float
	{
		return FMath::Tanh(FMath::Max(Value, 0.0f)) * 0.85f;
	};

	BassNorm = TanhNorm(Bass);
	MidsNorm = TanhNorm(Mids);
	TrebleNorm = TanhNorm(Treble);
	AmplitudeNorm = TanhNorm(Amplitude);
}

/** @brief Asymmetric smoothing — fast on rising values (AttackSpeed), slow on falling (DecaySpeed). */
float AAudioAnalysisMaster::SmoothValue(float Current, float Target, float DeltaTime) const
{
	const float Speed = (Target > Current) ? AttackSpeed : DecaySpeed;
	return FMath::FInterpTo(Current, Target, DeltaTime, Speed);
}

/** @brief Goertzel single-frequency magnitude extraction from a PCM buffer. */
float AAudioAnalysisMaster::GetMagnitudeAtFrequency(const TArray<float>& Buffer, int32 SampleRate, float Frequency) const
{
	const int32 N = Buffer.Num();
	if (N == 0 || SampleRate == 0)
	{
		return 0.0f;
	}

	const float K = Frequency * N / SampleRate;
	const float W = 2.0f * PI * K / N;
	const float Coeff = 2.0f * FMath::Cos(W);

	float S1 = 0.0f;
	float S2 = 0.0f;

	for (int32 i = 0; i < N; i++)
	{
		const float S0 = Buffer[i] + Coeff * S1 - S2;
		S2 = S1;
		S1 = S0;
	}

	const float MagSq = S1 * S1 + S2 * S2 - Coeff * S1 * S2;
	return (FMath::Sqrt(FMath::Max(MagSq, 0.0f)) * 2.0f / N) * 10.0f;
}
