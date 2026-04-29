//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Widgets/QuestionWindowBaseWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "QuitGameWindowWidget.generated.h"

/// <summary>
/// Quit game message widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UQuitGameWindowWidget : public UQuestionWindowBaseWidget
{
	GENERATED_BODY()
	
public:

	UQuitGameWindowWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UFUNCTION()
	void YesPressed();

	UFUNCTION()
	void NoPressed();

	UCommonActivatableWidgetContainerBase* ThisActivatableWidget;
};
