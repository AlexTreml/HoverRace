//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Widgets/SettingsParamBase.h"
#include "Components/TextBlock.h"
#include "SwitchWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentTriggerChange, USwitchWidget, OnSwitchChange, int, Value);

/// <summary>
/// Switch param setting widget
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API USwitchWidget : public USettingsParamBase
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftUnHoverEvent);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightUnHoverEvent);

public:

	USwitchWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* Left_Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* Right_Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* CurrentValueName;

	//Buttons
	UFUNCTION()
	void Left_Clicked();

	UFUNCTION()
	void Left_Pressed();

	UFUNCTION()
	void Left_Released();

	UFUNCTION()
	void Left_Hovered();

	UFUNCTION()
	void Left_UnHovered();

	UFUNCTION()
	void Right_Clicked();

	UFUNCTION()
	void Right_Pressed();

	UFUNCTION()
	void Right_Released();

	UFUNCTION()
	void Right_Hovered();

	UFUNCTION()
	void Right_UnHovered();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	int Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FText> ValueNames;

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE int GetSwitchValue() const { return Value; };

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE TArray<FText> GetValueNames() const { return ValueNames; };

	UPROPERTY(BlueprintAssignable, Category = "On Change")
	FComponentTriggerChange OnSwitchChange;

	void OnValueChanged(int NewValue);

	virtual void OnValueChangedV(int Value);

	void UpdateValueName();

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnLeftClickedEvent OnLeftClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnLeftPressedEvent OnLeftPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnLeftReleasedEvent OnLeftReleased;

	/** Called when the button is hovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnLeftHoverEvent OnLeftHovered;

	/** Called when the button is unhovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnLeftUnHoverEvent OnLeftUnHovered;


	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnRightClickedEvent OnRightClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnRightPressedEvent OnRightPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnRightReleasedEvent OnRightReleased;

	/** Called when the button is hovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnRightHoverEvent OnRightHovered;

	/** Called when the button is unhovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnRightUnHoverEvent OnRightUnHovered;
};
