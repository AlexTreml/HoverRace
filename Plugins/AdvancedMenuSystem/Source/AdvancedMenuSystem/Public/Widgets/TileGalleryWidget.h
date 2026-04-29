//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "TileGalleryWidget.generated.h"

/// <summary>
/// Item for gallery widget.
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FGalleryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UTexture2D* ImageTexture = nullptr;
};

/// <summary>
/// Gallery widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UTileGalleryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UImage* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* TitleTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* Left_Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* Right_Button;

	UTileGalleryWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnLeftPressed();

	UFUNCTION()
	void OnRightPressed();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FGalleryItem> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	int PreviewID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bLoop;

	int CurrentPosition;

	bool TransitionFinished;

	void OnValueChanged(int NewValue);

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "Transition Animation", BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> TransitionAnimationLeft;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "Transition Animation", BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> TransitionAnimationRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Transition", meta = (AllowPrivateAccess = "true", DisplayName = "Update Image Time"))
	float UpdateImageTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor TitleTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo TitleTextFont;

};