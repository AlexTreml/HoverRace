//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Save/Variables.h"
#include "CommonActivatableWidget.h"
#include "Components/Overlay.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "MenuBaseWidget.generated.h"

/// <summary>
/// Menu widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UMenuBaseWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartUnHoverEvent);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsUnHoverEvent);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitGameClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitGamePressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitGameReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitGameHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitGameUnHoverEvent);

public:

	UMenuBaseWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UOverlay* BodyOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* SettingsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* QuitGameButton;

	UPROPERTY(BlueprintReadOnly, Category = "Activatable", meta = (AllowPrivateAccess = "true"))
	class UCommonActivatableWidgetContainerBase* ActivatableWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UCommonActivatableWidgetContainerBase* TabActivatableWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UCommonActivatableWidgetContainerBase* WindowActivatableWidget;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	UCommonActivatableWidget* OpenWidget(TSubclassOf<UCommonActivatableWidget> Widget, bool OpenInTab);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	UCommonActivatableWidget* ShowDialogWindow(TSubclassOf<UCommonActivatableWidget> Widget, FText Message);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void RemoveDialogWindow();

	UFUNCTION()
	void Start_Clicked();

	UFUNCTION()
	void Start_Pressed();

	UFUNCTION()
	void Start_Released();

	UFUNCTION()
	void Start_Hovered();

	UFUNCTION()
	void Start_UnHovered();

	UFUNCTION()
	void Settings_Pressed();

	UFUNCTION()
	void Settings_Clicked();

	UFUNCTION()
	void Settings_Released();

	UFUNCTION()
	void Settings_Hovered();

	UFUNCTION()
	void Settings_UnHovered();

	UFUNCTION()
	void QuitGame_Pressed();

	UFUNCTION()
	void QuitGame_Clicked();

	UFUNCTION()
	void QuitGame_Released();

	UFUNCTION()
	void QuitGame_Hovered();

	UFUNCTION()
	void QuitGame_UnHovered();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bOpenTabFullScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bHasStartButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Start", meta = (AllowPrivateAccess = "true", EditCondition = "bHasStartButton == true", EditConditionHides))
	EOpenWidgetTypes DoOnStartType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bHasSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Settings", meta = (AllowPrivateAccess = "true", EditCondition = "bHasSettings == true", EditConditionHides))
	EOpenWidgetTypes DoOnSettingsType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bHasQuitGame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Quit Game", meta = (AllowPrivateAccess = "true", EditCondition = "bHasQuitGame == true", EditConditionHides))
	EOpenWidgetTypes DoOnQuitGameType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Start", meta = (AllowPrivateAccess = "true", EditCondition = "bHasStartButton == true && DoOnStartType == EOpenWidgetTypes::OpenWidget", EditConditionHides))
	TSubclassOf<UCommonActivatableWidget> StartWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Settings", meta = (AllowPrivateAccess = "true", EditCondition = "bHasSettings == true && DoOnSettingsType == EOpenWidgetTypes::OpenWidget", EditConditionHides))
	TSubclassOf<UCommonActivatableWidget> SettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Quit Game", meta = (AllowPrivateAccess = "true", EditCondition = "bHasQuitGame == true && DoOnQuitGameType == EOpenWidgetTypes::OpenWidget", EditConditionHides))
	TSubclassOf<UCommonActivatableWidget> QuitGameWidget;

	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnStartClickedEvent OnStartClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnStartPressedEvent OnStartPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnStartReleasedEvent OnStartReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnStartHoverEvent OnStartHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnStartUnHoverEvent OnStartUnHovered;

	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSettingsClickedEvent OnSettingsClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSettingsPressedEvent OnSettingsPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSettingsReleasedEvent OnSettingsReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSettingsHoverEvent OnSettingsHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSettingsUnHoverEvent OnSettingsUnHovered;

	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnQuitGameClickedEvent OnQuitClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnQuitGamePressedEvent OnQuitPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnQuitGameReleasedEvent OnQuitReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnQuitGameHoverEvent OnQuitHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnQuitGameUnHoverEvent OnQuitUnHovered;

	UCommonActivatableWidget* SettingsActivatableWidget;

	bool bSettingsOpened;

	bool bStartOpened;

	void UpdateSettingOpened();
};
