//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/LoadingScreenWidget.h"
#include "Kismet/KismetMathLibrary.h"

ULoadingScreenWidget::ULoadingScreenWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ULoadingScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (bRunProgressOnStart)
    {
        PlayAnimationForward(AutoLoadingAnimation, 1.f);
    }
}

void ULoadingScreenWidget::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    if (ProgressBar)
    {
        ProgressBar->SetWidgetStyle(WidgetStyle);
        ProgressBar->SetPercent(Percent);
        ProgressBar->SetBarFillType(BarFillType);
        ProgressBar->SetBarFillStyle(BarFillStyle);
        ProgressBar->SetIsMarquee(bIsMarquee);
        ProgressBar->SetBorderPadding(BorderPadding);
        ProgressBar->SetFillColorAndOpacity(FillColorAndOpacity);
        ProgressBar->FillColorAndOpacityDelegate = FillColorAndOpacityDelegate;
    }
}

void ULoadingScreenWidget::StartLoad()
{
    DoOnLoadStart.Broadcast();
}

void ULoadingScreenWidget::ProgressLoad(float Value)
{
    Percent = Value;
    ProgressBar->SetPercent(Percent);

    OnValueChange.Broadcast(Percent);
}

void ULoadingScreenWidget::EndtLoad()
{
    DoOnLoadEnd.Broadcast();
}

void ULoadingScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bUseAutoProgress)
    {
        if (IsAnimationPlaying(AutoLoadingAnimation) && !bStarted)
        {
            if (bFinished)
            {
                bFinished = false;
            }

            bStarted = true;

            StartLoad();
        }
        else if (bStarted && !IsAnimationPlaying(AutoLoadingAnimation))
        {
            bFinished = true;
            bStarted = false;

            EndtLoad();
        }
    }
    else
    {
        if (Percent == 0.f && !bStarted)
        {
            if (bFinished)
            {
                bFinished = false;
            }

            bStarted = true;

            StartLoad();
        }
        else if (bStarted && Percent == 1.f)
        {
            bFinished = true;
            bStarted = false;

            EndtLoad();
        }
    }
}