//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MovableWindowHeaderWidget.generated.h"

/// <summary>
/// Movable header for the window.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UMovableWindowHeaderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonPressed);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonHovered);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonReleased);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonUnHovered);

	UMovableWindowHeaderWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	virtual void PostLoad() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* TitleTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* HeaderButton;

	UFUNCTION(BlueprintSetter)
	void SetTitleText(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextFont(FSlateFontInfo Font);

	void UpdateTextBlock();

	UFUNCTION()
	void DoOnPressed();

	UFUNCTION()
	void DoOnHovered();

	UFUNCTION()
	void DoOnReleased();

	UFUNCTION()
	void DoOnUnHovered();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonPressed DoOnButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonHovered DoOnButtonHovered;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonReleased DoOnButtonReleased;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonUnHovered DoOnButtonUnHovered;

	/*Title text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleText, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextColor, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor TitleTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextFont, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo TitleTextFont;



};
