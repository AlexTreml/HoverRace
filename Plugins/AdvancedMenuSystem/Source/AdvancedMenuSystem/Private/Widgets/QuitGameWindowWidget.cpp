//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/QuitGameWindowWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UQuitGameWindowWidget::UQuitGameWindowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MessageText = FText::AsCultureInvariant("Are you sure?");
}

void UQuitGameWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnYesPressed.Clear();

	OnNoPressed.Clear();

	OnYesPressed.AddDynamic(this, &UQuitGameWindowWidget::YesPressed);

	OnNoPressed.AddDynamic(this, &UQuitGameWindowWidget::NoPressed);
}

void UQuitGameWindowWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UQuitGameWindowWidget::YesPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

void UQuitGameWindowWidget::NoPressed()
{
	if (ThisActivatableWidget)
	{
		ThisActivatableWidget->ClearWidgets();
	}
}