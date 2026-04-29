#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioAnalysisMaster.generated.h"

class USoundSubmix;

/**
 * Real-time audio analysis via Submix listener.
 * Captures live PCM data and extracts bass, mid, treble, and amplitude
 * using the Goertzel algorithm (efficient single-frequency DFT).
 * No baked data required — works with any audio playing through the submix.
 */
UCLASS()
class HOVERVEHICLESYSTEM_API AAudioAnalysisMaster : public AActor
{
	GENERATED_BODY()

public:
	AAudioAnalysisMaster();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	/** Called by the internal submix listener helper — do not call directly. */
	void HandleNewSubmixBuffer(float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate);

	// ========== SOURCE ==========

	/** Submix to analyse. Leave empty to use the master submix (all game audio). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Source")
	USoundSubmix* Submix;

	// ========== FREQUENCY BAND OUTPUT ==========

	/** Current bass energy (low frequencies ~20-250 Hz) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float Bass;

	/** Current mid energy (mid frequencies ~250-4000 Hz) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float Mids;

	/** Current treble energy (high frequencies ~4000-20000 Hz) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float Treble;

	/** Overall amplitude (envelope) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float Amplitude;

	/** Normalised 0-1 values (after gain and clamp) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float BassNorm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float MidsNorm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float TrebleNorm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analysis|Output")
	float AmplitudeNorm;

	// ========== SETTINGS ==========

	/** Gain multiplier for bass band */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Gain", meta = (ClampMin = "0.1"))
	float BassGain = 3.0f;

	/** Gain multiplier for mids band */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Gain", meta = (ClampMin = "0.1"))
	float MidsGain = 5.0f;

	/** Gain multiplier for treble band */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Gain", meta = (ClampMin = "0.1"))
	float TrebleGain = 8.0f;

	/** Gain multiplier for amplitude */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Gain", meta = (ClampMin = "0.1"))
	float AmplitudeGain = 2.0f;

	/** How quickly values rise (higher = snappier reaction) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Smoothing", meta = (ClampMin = "1.0", ClampMax = "50.0"))
	float AttackSpeed = 15.0f;

	/** How quickly values fall (lower = longer tails) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Smoothing", meta = (ClampMin = "1.0", ClampMax = "50.0"))
	float DecaySpeed = 5.0f;

	// ========== FREQUENCY BAND RANGES ==========

	/** Low end of bass band (Hz) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Frequency Bands")
	float BassMinFreq = 20.0f;

	/** High end of bass band / low end of mids (Hz) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Frequency Bands")
	float BassMaxFreq = 250.0f;

	/** High end of mids / low end of treble (Hz) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Frequency Bands")
	float MidsMaxFreq = 4000.0f;

	/** High end of treble band (Hz) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analysis|Frequency Bands")
	float TrebleMaxFreq = 20000.0f;

private:
	float SmoothValue(float Current, float Target, float DeltaTime) const;
	float GetMagnitudeAtFrequency(const TArray<float>& Buffer, int32 SampleRate, float Frequency) const;

	/** Helper object that implements ISubmixBufferListener (avoids MI with UObject). */
	TSharedPtr<class FSubmixListenerHelper, ESPMode::ThreadSafe> SubmixListener;

	/** Thread-safe buffer exchange between audio thread and game thread. */
	FCriticalSection BufferCriticalSection;
	TArray<float> CapturedBuffer;
	int32 CapturedSampleRate = 0;
	bool bHasNewData = false;
};
