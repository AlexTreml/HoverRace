//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/QuestionWindowBaseWidget.h"

UQuestionWindowBaseWidget::UQuestionWindowBaseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UQuestionWindowBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	YesButton->OnClicked.Clear();
	YesButton->OnPressed.Clear();
	YesButton->OnReleased.Clear();
	YesButton->OnHovered.Clear();
	YesButton->OnUnhovered.Clear();

	NoButton->OnClicked.Clear();
	NoButton->OnPressed.Clear();
	NoButton->OnReleased.Clear();
	NoButton->OnHovered.Clear();
	NoButton->OnUnhovered.Clear();

	YesButton->OnClicked.AddDynamic(this, &UQuestionWindowBaseWidget::Yes_Clicked);
	YesButton->OnPressed.AddDynamic(this, &UQuestionWindowBaseWidget::Yes_Pressed);
	YesButton->OnReleased.AddDynamic(this, &UQuestionWindowBaseWidget::Yes_Released);
	YesButton->OnHovered.AddDynamic(this, &UQuestionWindowBaseWidget::Yes_Hovered);
	YesButton->OnUnhovered.AddDynamic(this, &UQuestionWindowBaseWidget::Yes_UnHovered);

	NoButton->OnClicked.AddDynamic(this, &UQuestionWindowBaseWidget::No_Clicked);
	NoButton->OnPressed.AddDynamic(this, &UQuestionWindowBaseWidget::No_Pressed);
	NoButton->OnReleased.AddDynamic(this, &UQuestionWindowBaseWidget::No_Released);
	NoButton->OnHovered.AddDynamic(this, &UQuestionWindowBaseWidget::No_Hovered);
	NoButton->OnUnhovered.AddDynamic(this, &UQuestionWindowBaseWidget::No_UnHovered);
}

void UQuestionWindowBaseWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Message)
	{
		Message->SetText(MessageText);
		Message->SetColorAndOpacity(MessageTextColor);
		Message->SetFont(MessageTextFont);
	}

}

void UQuestionWindowBaseWidget::Yes_Clicked()
{
	OnYesClicked.Broadcast();
}

void UQuestionWindowBaseWidget::Yes_Pressed()
{
	OnYesPressed.Broadcast();
}

void UQuestionWindowBaseWidget::Yes_Released()
{
	OnYesReleased.Broadcast();
}

void UQuestionWindowBaseWidget::Yes_Hovered()
{
	OnYesHovered.Broadcast();
}

void UQuestionWindowBaseWidget::Yes_UnHovered()
{
	OnYesUnHovered.Broadcast();
}

void UQuestionWindowBaseWidget::No_Clicked()
{
	OnNoClicked.Broadcast();
}

void UQuestionWindowBaseWidget::No_Pressed()
{
	OnNoPressed.Broadcast();
}

void UQuestionWindowBaseWidget::No_Released()
{
	OnNoReleased.Broadcast();
}

void UQuestionWindowBaseWidget::No_Hovered()
{
	OnNoHovered.Broadcast();
}

void UQuestionWindowBaseWidget::No_UnHovered()
{
	OnNoUnhovered.Broadcast();
}

void UQuestionWindowBaseWidget::SetMessageText(FText NewMessage)
{
	MessageText = NewMessage;
}