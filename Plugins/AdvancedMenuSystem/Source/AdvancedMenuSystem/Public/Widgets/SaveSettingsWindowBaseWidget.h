//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Widgets/QuestionWindowBaseWidget.h"
#include "Widgets/MenuSettingsWidget.h"
#include "Widgets/MenuBaseWidget.h"
#include "SaveSettingsWindowBaseWidget.generated.h"

/// <summary>
/// Save settings message widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API USaveSettingsWindowBaseWidget : public UQuestionWindowBaseWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseSettingsEvent);

public:

	USaveSettingsWindowBaseWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UFUNCTION()
	void YesPressed();

	UFUNCTION()
	void NoPressed();

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FCloseSettingsEvent OnCloseSettings;

	void SetSettingsWidget(UMenuSettingsWidget* Widget);

	UMenuSettingsWidget* MenuSettingsWidget;

	UMenuBaseWidget* MenuBaseWidget;

	UCommonActivatableWidgetContainerBase* ThisActivatableWidget;


	bool bAutoClouse;
};
