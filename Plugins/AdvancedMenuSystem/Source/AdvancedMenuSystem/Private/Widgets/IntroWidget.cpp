


#include "Widgets/IntroWidget.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Widgets/MenuBaseWidget.h"

UIntroWidget::UIntroWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		BottomTextFont = DefaultFont;
	}

	BottomText = FText::AsCultureInvariant(FString());
	BottomTextColor = FColor::White;
	FadeSpeed = 1.f;
	LogoShowTime = 5.f;
	LogoChangeDelay = 2.f;
	EndChangeTime = 0.5f;
	bStartOnSpawn = true;
	IntroFinished = false;
	bIsFocusable = true;

}


void UIntroWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bStartOnSpawn && !IntroFinished)
	{
		StartLogoShowcase();
	}

	SetKeyboardFocus();
}

void UIntroWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdateBottomTextBlock();
}

void UIntroWidget::UpdateBottomTextBlock()
{
	if (BottomTextBlock)
	{
		BottomTextBlock->SetText(BottomText);
		BottomTextBlock->SetColorAndOpacity(BottomTextColor);
		BottomTextBlock->SetFont(BottomTextFont);
	}
}

void UIntroWidget::StartLogoShowcase()
{
	ShowedLogos = 0;
 	ProcedAllLogos(ShowedLogos);
}

void UIntroWidget::ProcedAllLogos(int i)
{
	ShowedLogos = i;

	if (GetWorld() && this && LogoImages.Num() && i < LogoImages.Num() && LogoImages[i] && !IntroFinished)
	{
		LogoImage->SetBrushFromTexture(LogoImages[i]);

		PlayAnimationForward(LogoFadeAnimation, FadeSpeed);

		GetWorld()->GetTimerManager().ClearTimer(handle);

		GetWorld()->GetTimerManager().SetTimer(
			handle, [this]()
			{
				if (GetWorld() && this && !IntroFinished)
				{
					PlayAnimationReverse(LogoFadeAnimation, FadeSpeed);

					GetWorld()->GetTimerManager().ClearTimer(HandleLoop);

					GetWorld()->GetTimerManager().SetTimer(
						HandleLoop, [this]()
						{
							if (GetWorld() && this && !IntroFinished)
							{
								++ShowedLogos;
								ProcedAllLogos(ShowedLogos);
							}
						},
						LogoChangeDelay, false);

				}
			},
			LogoShowTime, false);

	}
	else if (GetWorld() && this && i == LogoImages.Num() && !IntroFinished)
	{
		if (bUseBackgroundFade)
		{
			PlayAnimationForward(BackgroundFadeAnimation);
		}

		GetWorld()->GetTimerManager().ClearTimer(HandleLoop);

		GetWorld()->GetTimerManager().SetTimer(
			HandleLoop, [this]()
			{
				if (GetWorld() && this && !IntroFinished)
				{
					CheckEndIntroWindowChange();
				}
			},
			EndChangeTime, false);

	}
}

void UIntroWidget::CheckEndIntroWindowChange()
{
	DoOnIntroEnd.Broadcast();

	IntroFinished = true;

	GetWorld()->GetTimerManager().ClearTimer(handle);
	GetWorld()->GetTimerManager().ClearTimer(HandleLoop);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	if (ActivatableWidget)
	{
		ActivatableWidget->ClearWidgets();

		UCommonActivatableWidget* CurrentActivatableWidget = ActivatableWidget->AddWidget(MainMenuWidget);

		if (CurrentActivatableWidget && CurrentActivatableWidget->GetClass()->IsChildOf(UMenuBaseWidget::StaticClass()))
		{
			UMenuBaseWidget* MenuBox = Cast<UMenuBaseWidget>(CurrentActivatableWidget);

			MenuBox->ActivatableWidget = ActivatableWidget;
		}
	}
}

FReply UIntroWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	CheckEndIntroWindowChange();

	return OnKeyDown(InGeometry, InKeyEvent).NativeReply;
}