//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "MenuScreenWidget.generated.h"

/// <summary>
/// Menu screen widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UMenuScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMenuScreenWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	/// <summary>
	/// Main Activatable Widget which displays menu and intro.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UCommonActivatableWidgetContainerBase* MainMenuActivatableWidget;

	/// <summary>
	/// Whether or not widget has intro.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bHasIntro;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true", EditCondition = "bHasIntro == true"))
	TSubclassOf<UCommonActivatableWidget> IntroWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonActivatableWidget> MainMenuWidget;

	/// <summary>
	/// Dispalys the widget.
	/// </summary>
	/// <param name="Class"></param>
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void SetMainScreen(TSubclassOf<UCommonActivatableWidget> Class);

	UFUNCTION(BlueprintCallable, Category = "Menu")
	UCommonActivatableWidget* OpenWidget(TSubclassOf<UCommonActivatableWidget> Widget, bool OpenInTab);

	UCommonActivatableWidget* CurrentActivatableWidget;
};
