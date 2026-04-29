//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/CreditsWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScrollBoxSlot.h"

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bHasSkipButton = true;
	ScrollSpeed = 1.f;
	SectionTitleTextColor = FColor(1.f, 1.f, 1.f, 1.f);
	SectionBodyTextColor = FColor(1.f, 1.f, 1.f, 1.f);
}

void UCreditsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!bHasSkipButton)
	{
		SkipButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	AddCreditText();

	SkipButton->OnPressed.Clear();

	SkipButton->OnPressed.AddDynamic(this, &UCreditsWidget::OnSkipPress);
}

void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScrollBox->SetScrollOffset(0.f);

}

void UCreditsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	ScrollTheBox(InDeltaTime);
}

void UCreditsWidget::ScrollTheBox(float InDeltaTime)
{
	float NewCurrentScroll = ScrollBox->GetScrollOffset() + (ScrollSpeed * InDeltaTime);
	if (NewCurrentScroll >= 0.f)
	{
		if (NewCurrentScroll <= ScrollBox->GetScrollOffsetOfEnd())
		{
			ScrollBox->SetScrollOffset(NewCurrentScroll);
		}
		else
		{
			ScrollBox->SetScrollOffset(ScrollBox->GetScrollOffsetOfEnd());

			bFinished = true;

			OnCreditsFinished.Broadcast();

			if (bCloseOnFinish)
			{
				CloseCredits();
			}
		}
	}
	else
	{
		ScrollBox->SetScrollOffset(0.f);
	}
}

void UCreditsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UCreditsWidget::AddCreditText()
{
	if (SectionsBoxes.IsEmpty() && Sections.Num())
	{
		for (int i = 0; i < Sections.Num(); i++)
		{
			UVerticalBox* SectionBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), *(FString("SectionBox") + FString::FromInt(i)));

			UTextBlock* SectionTitleLine = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), *(FString("SectionTitle") + FString::FromInt(i)));

			SectionTitleLine->SetText(Sections[i].Title);
			SectionTitleLine->SetColorAndOpacity(SectionTitleTextColor);
			SectionTitleLine->SetFont(SectionTitleTextFont);
			SectionTitleLine->SetJustification(Justification);
			SectionTitleLine->SetMargin(TitleTextMargin);

			const auto RootWidgetSlot0 = ScrollBox->AddChild(SectionBox);

			SectionsBoxes.Add(SectionBox);

			if (RootWidgetSlot0)
			{
				UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(RootWidgetSlot0);

				if (ScrollBoxSlot)
				{
					ScrollBoxSlot->SetPadding(SectionsMargin);
				}
			}

			const auto RootWidgetSlot1 = SectionBox->AddChild(SectionTitleLine);

			TitleLines.Add(SectionTitleLine);

			for (int J = 0; J < Sections[i].LineArray.Num(); J++)
			{
				UTextBlock* SectionBodyLine = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), *(FString("SectionBody") + FString::FromInt(i) +":"+ FString::FromInt(J)));

				SectionBodyLine->SetText(Sections[i].LineArray[J]);
				SectionBodyLine->SetColorAndOpacity(SectionBodyTextColor);
				SectionBodyLine->SetFont(SectionBodyTextFont);
				SectionBodyLine->SetJustification(Justification);
				SectionBodyLine->SetMargin(BodyTextMargin);

				const auto RootWidgetSlot2 = SectionBox->AddChild(SectionBodyLine);

				BodyLines.Add(SectionBodyLine);
			}
		}
	}
}

void UCreditsWidget::SetTitleTextColor(FColor Color)
{
	SectionTitleTextColor = Color;
}

void UCreditsWidget::SetTitleTextFont(FSlateFontInfo Font)
{
	SectionTitleTextFont = Font;
}

void UCreditsWidget::SetBodyTextColor(FColor Color)
{
	SectionBodyTextColor = Color;
}

void UCreditsWidget::SetBodyTextFont(FSlateFontInfo Font)
{
	SectionBodyTextFont = Font;
}

void UCreditsWidget::OnSkipPress()
{
	CloseCredits();
}

void UCreditsWidget::CloseCredits()
{
	OnCreditsClose.Broadcast();

	if (SkipType == ESkipTypes::RemoveWidget)
	{
		RemoveFromParent();
	}
	else
	{
		if (ActivatableWidget)
		{
			ActivatableWidget->ClearWidgets();
			UCommonActivatableWidget* ActivatedWidget = ActivatableWidget->AddWidget(ActivatableWidgetToOpen);
		}
	}
}