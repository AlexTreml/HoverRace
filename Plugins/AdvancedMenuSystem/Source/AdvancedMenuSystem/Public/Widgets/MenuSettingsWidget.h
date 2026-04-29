//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonActivatableWidget.h"
#include "Components/Button.h"
#include "MenuSettingsWidget.generated.h"

/// <summary>
/// Menu settings widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UMenuSettingsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveToWidgetEvent);

public:

	UMenuSettingsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UOverlay* BodyOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* VideoButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* GraphicsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* ControlsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* AudioButton;

	UCommonActivatableWidgetContainerBase* MainMenuActivatableWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UCommonActivatableWidgetContainerBase* SettingsActivatableWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UCommonActivatableWidgetContainerBase* QuestionActivatableWidget;

	UFUNCTION()
	void Back_Pressed();

	UFUNCTION()
	void Video_Pressed();

	UFUNCTION()
	void Graphics_Pressed();

	UFUNCTION()
	void Controls_Pressed();

	UFUNCTION()
	void Audio_Pressed();

	UFUNCTION()
	void OpenVideo();

	UFUNCTION()
	void OpenGraphics();

	UFUNCTION()
	void OpenControls();

	UFUNCTION()
	void OpenAudio();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> MainMenuWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> VideoSettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> GraphicsSettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> AudioSettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> ControlsSettingsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> WindowSaveWidget;

	UCommonActivatableWidget* CurrentActivatedWidget;

	UCommonActivatableWidgetContainerBase* SaveWindowActivatedWidget;

	UCommonActivatableWidget* SaveActivatedWidget;

	UCommonActivatableWidget* ParentMenu;

	bool bIsInFullscreen;

	void CloseSettings();

	bool CheckSettingsChanged();

	void OpenSaveChangesDialog(bool AutoClouse);

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FMoveToWidgetEvent OnMoveToWidgetEvent;

	void SaveChanges(bool CloseSettings);

	void CloseSettingsForce();

	UFUNCTION()
	void CloseSettingsFullScreen();

	UFUNCTION()
	void CloseSettingsTab();

	UFUNCTION()
	void CloseSaveWindow();

};
