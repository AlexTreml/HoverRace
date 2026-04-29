//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"
#include "Save/Variables.h"
#include "Math/Color.h"
#include "Fonts/SlateFontInfo.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Components/VerticalBox.h"
#include "CreditsWidget.generated.h"

/// <summary>
/// Credits widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UCreditsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreditsFinished);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreditsClose);

	/*Components*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UButton* SkipButton;

	/*Functions*/
	UCreditsWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct();

	virtual void SynchronizeProperties() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	/// <summary>
	/// Whether or not has the skip button.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bHasSkipButton;

	/// <summary>
	/// Credits scroll speed.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float ScrollSpeed;

	/// <summary>
	/// Text Sections
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FCreditSection> Sections;

	/// <summary>
	/// Margin beetwen sections.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FMargin SectionsMargin;

	/// <summary>
	/// Credits text justification.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ETextJustify::Type> Justification;


	TArray<UVerticalBox*> SectionsBoxes;

	TArray<UTextBlock*> TitleLines;

	TArray<UTextBlock*> BodyLines;

	void ScrollTheBox(float InDeltaTime);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextFont(FSlateFontInfo Font);

	UFUNCTION(BlueprintSetter)
	void SetBodyTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetBodyTextFont(FSlateFontInfo Font);

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE bool IsFinished() const { return bFinished; };

	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnCreditsClose OnCreditsClose;

	UPROPERTY(BlueprintAssignable, Category = "Widget Event")
	FOnCreditsFinished OnCreditsFinished;

	/*Title text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextColor, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor SectionTitleTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextFont, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo SectionTitleTextFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true"))
	FMargin TitleTextMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetBodyTextColor, Category = "Settings|Body Text", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor SectionBodyTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetBodyTextFont, Category = "Settings|Body Text", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo SectionBodyTextFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Body Text", meta = (AllowPrivateAccess = "true"))
	FMargin BodyTextMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Skip", meta = (AllowPrivateAccess = "true", DisplayName = "Skip Type"))
	ESkipTypes SkipType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Skip", meta = (AllowPrivateAccess = "true", DisplayName = "Close When Finished"))
	bool bCloseOnFinish;

	UPROPERTY(BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	UCommonActivatableWidgetContainerBase* ActivatableWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Skip", meta = (AllowPrivateAccess = "true", EditCondition = "SkipType == ESkipTypes::ToWidget"))
	TSubclassOf<UCommonActivatableWidget> ActivatableWidgetToOpen;

	UPROPERTY(BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	bool bFinished;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void CloseCredits();

protected:

	void AddCreditText();

	UFUNCTION()
	void OnSkipPress();

};
