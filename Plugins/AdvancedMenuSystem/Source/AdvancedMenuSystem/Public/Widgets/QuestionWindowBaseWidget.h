//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "QuestionWindowBaseWidget.generated.h"

/// <summary>
/// Message widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UQuestionWindowBaseWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYesClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYesPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYesReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYesHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYesUnHoverEvent);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoUnHoverEvent);

public:

	UQuestionWindowBaseWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	/// <summary>
	/// Message text block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* Message;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* YesButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* NoButton;

	/// 

	UFUNCTION()
	void Yes_Clicked();

	UFUNCTION()
	void Yes_Pressed();

	UFUNCTION()
	void Yes_Released();

	UFUNCTION()
	void Yes_Hovered();

	UFUNCTION()
	void Yes_UnHovered();

	/// 

	UFUNCTION()
	void No_Clicked();

	UFUNCTION()
	void No_Pressed();

	UFUNCTION()
	void No_Released();

	UFUNCTION()
	void No_Hovered();

	UFUNCTION()
	void No_UnHovered();

	/// <summary>
	/// Set the new message text.
	/// </summary>
	/// <param name="NewMessage">New Message</param>
	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetMessageText(FText NewMessage);

	/// <summary>
	/// Text of the Message Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Message", meta = (AllowPrivateAccess = "true"))
	FText MessageText;

	/// <summary>
	/// Color of the Message Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Message", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor MessageTextColor;

	/// <summary>
	/// Font of the Message Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Message", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo MessageTextFont;

	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnYesClickedEvent OnYesClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnYesPressedEvent OnYesPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnYesReleasedEvent OnYesReleased;

	/** Called when the button is hovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnYesHoverEvent OnYesHovered;

	/** Called when the button is unhovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnYesUnHoverEvent OnYesUnHovered;


	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnNoClickedEvent OnNoClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnNoPressedEvent OnNoPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnNoReleasedEvent OnNoReleased;

	/** Called when the button is hovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnNoHoverEvent OnNoHovered;

	/** Called when the button is unhovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnNoUnHoverEvent OnNoUnhovered;
};
