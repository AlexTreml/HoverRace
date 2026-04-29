//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/TileGalleryWidget.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/TimerHandle.h"
#include "TimerManager.h"

UTileGalleryWidget::UTileGalleryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		TitleTextFont = DefaultFont;
	}

	TitleTextColor = FColor::White;

	CurrentPosition = 0;
	PreviewID = 0;
	UpdateImageTime = 1.f;

	TransitionFinished = true;
}


void UTileGalleryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Items.Num())
	{
		TitleTextBlock->SetText(Items[CurrentPosition].Title);
		Image->SetBrushFromTexture(Items[CurrentPosition].ImageTexture);
	}

	if (!Left_Button->OnPressed.IsAlreadyBound(this, &UTileGalleryWidget::OnLeftPressed))
	{
		Left_Button->OnPressed.AddDynamic(this, &UTileGalleryWidget::OnLeftPressed);
	}

	if (!Right_Button->OnPressed.IsAlreadyBound(this, &UTileGalleryWidget::OnRightPressed))
	{
		Right_Button->OnPressed.AddDynamic(this, &UTileGalleryWidget::OnRightPressed);
	}
}

void UTileGalleryWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Items.Num() && TransitionFinished)
	{
		int ID = 0;

		if (PreviewID < Items.Num())
		{
			ID = PreviewID;
		}

		if (TitleTextBlock && Image)
		{
			TitleTextBlock->SetText(Items[ID].Title);
			TitleTextBlock->SetFont(TitleTextFont);
			TitleTextBlock->SetColorAndOpacity(TitleTextColor);
			Image->SetBrushFromTexture(Items[ID].ImageTexture);
		}
	}
}

void UTileGalleryWidget::OnLeftPressed()
{
	if (Items.Num() && TransitionFinished)
	{
		PlayAnimationForward(TransitionAnimationLeft, 1.f);

		if (CurrentPosition > 0)
		{
			--CurrentPosition;

			OnValueChanged(CurrentPosition);
		}
		else if (bLoop)
		{
			CurrentPosition = Items.Num() - 1;

			OnValueChanged(CurrentPosition);
		}
	}
}

void UTileGalleryWidget::OnRightPressed()
{
	if (Items.Num() && TransitionFinished)
	{
		PlayAnimationForward(TransitionAnimationRight, 1.f);

		if (CurrentPosition < Items.Num() - 1)
		{
			++CurrentPosition;

			OnValueChanged(CurrentPosition);
		}
		else if (bLoop)
		{
			CurrentPosition = 0;

			OnValueChanged(CurrentPosition);
		}
	}
}

void UTileGalleryWidget::OnValueChanged(int NewValue)
{
	if (Items.Num() && CurrentPosition < Items.Num())
	{
		TransitionFinished = false;

		FTimerHandle handle0;
		FTimerHandle handle1;

		GetWorld()->GetTimerManager().SetTimer(
			handle0, [this]()
			{
				TitleTextBlock->SetText(Items[CurrentPosition].Title);
				Image->SetBrushFromTexture(Items[CurrentPosition].ImageTexture);
			},
			UpdateImageTime, false);

		GetWorld()->GetTimerManager().SetTimer(
			handle1, [this]()
			{
				TransitionFinished = true;
			},
			UpdateImageTime*2.f, false);

	}
}