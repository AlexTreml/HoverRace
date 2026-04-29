//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Materials/Material.h"
#include "Math/Color.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Fonts/SlateFontInfo.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "TileWidget.generated.h"

/// <summary>
/// Tile widget. 
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UTileWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonPressed);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonHovered);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonReleased);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnButtonUnHovered);

	UTileWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	UFUNCTION()
	void DoOnPressed();

	UFUNCTION()
	void DoOnHovered();

	UFUNCTION()
	void DoOnReleased();

	UFUNCTION()
	void DoOnUnHovered();

	void UpdateTileGeneralValues();

	void UpdateTileTintValues();

	void UpdateBackgroundImageValues();

	void UpdateGradientFadeValues();

	UFUNCTION(BlueprintSetter)
	void SetTintTile(bool Value);

	UFUNCTION(BlueprintSetter)
	void SetUseBackgroundImage(bool Value);

	UFUNCTION(BlueprintSetter)
	void SetUseGradientFade(bool Value);

	UFUNCTION(BlueprintSetter)
	void SetGradientFadeIntensivity(float Value);

	UFUNCTION(BlueprintSetter)
	void SetTintColor(FColor Value);

	UFUNCTION(BlueprintSetter)
	void SetTileColor(FColor Value);

	UFUNCTION(BlueprintSetter)
	void SetTileImage(UTexture* Image);

	UFUNCTION(BlueprintSetter)
	void SetTileDimentions(FVector2D Dimentions);

	UFUNCTION(BlueprintSetter)
	void SetCornerRadius(float Value);

	UFUNCTION(BlueprintSetter)
	void SetSharpness(float Value);

	UFUNCTION(BlueprintSetter)
	void SetTintIntensivity(float Value);

	UFUNCTION(BlueprintSetter)
	void SetUseCustomTileMaterial(bool Value);

	UFUNCTION(BlueprintSetter)
	void SetBackgroundOpacity(float Value);

	UFUNCTION(BlueprintSetter)
	void SetTileMaterial(UMaterial* Material);

	UFUNCTION(BlueprintSetter)
	void SetTitleText(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextFont(FSlateFontInfo Font);

	void UpdateTextBlock();

	void UpdateDescriptionTextBlock();

	UFUNCTION(BlueprintSetter)
	void SetDescriptionText(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetDescriptionTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetDescriptionTextFont(FSlateFontInfo Font);

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonPressed DoOnButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonHovered DoOnButtonHovered;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonReleased DoOnButtonReleased;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnButtonUnHovered DoOnButtonUnHovered;

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void SynchronizeProperties() override;

	/*Components*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UVerticalBox* VerticalTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* TitleTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* DescriptionTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* Button;

	/*General settings*/

	/*Title text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleText, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextColor, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor TitleTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextFont, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo TitleTextFont;

	/*Description line settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDescriptionText, Category = "Settings|Description", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText DescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDescriptionTextColor, Category = "Settings|Description", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor DescriptionTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDescriptionTextFont, Category = "Settings|Description", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo DescriptionTextFont;

	/*Backgroud settings*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Background", meta = (AllowPrivateAccess = "true"))
	bool bMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTintTile,  Category = "Settings|Background", meta = (AllowPrivateAccess = "true"))
	bool bTintTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUseBackgroundImage, Category = "Settings|Background", meta = (AllowPrivateAccess = "true"))
	bool bBackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter =  SetUseGradientFade,Category = "Settings|Background", meta = (AllowPrivateAccess = "true"))
	bool bGradientFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetGradientFadeIntensivity, Category = "Settings|Background", meta = (DisplayName = "Gradient Fade Intensivity", EditCondition = "bGradientFade == true", EditConditionHides))
	float GradientFadeIntensivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTintColor, Category = "Settings|Background",meta = (DisplayName = "Tint Color", EditCondition = "bFadeTile == true", EditConditionHides))
	FColor TintColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTileColor, Category = "Settings|Background", meta = (DisplayName = "Tile Color", EditCondition = "bBackgroundImage == false", EditConditionHides))
	FColor TileColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTileImage, Category = "Settings|Background", meta = (DisplayName = "Tile Image", EditCondition = "bBackgroundImage == true", EditConditionHides))
	UTexture* TileImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTileDimentions, Category = "Settings|Background", meta = (AllowPrivateAccess = "true"))
	FVector2D TileDimentions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCornerRadius, Category = "Settings|Background", meta = (AllowPrivateAccess = "true", ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float CornerRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetSharpness, Category = "Settings|Background", meta = (AllowPrivateAccess = "true", ClampMin = "0.0", UIMin = "0.0"))
	float Sharpness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTintIntensivity, Category = "Settings|Background", meta = (DisplayName = "Tint Intensivity", EditCondition = "bFadeTile == true", ClampMin = "0.0", UIMin = "0.0", EditConditionHides))
	float TintIntensivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUseCustomTileMaterial, Category = "Settings|Background", meta = (AllowPrivateAccess = "true"))
	bool bCustomTileMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetBackgroundOpacity, Category = "Settings|Background", meta = (DisplayName = "BackgroundOpacity", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditConditionHides))
	float BackgroundOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTileMaterial, Category = "Settings|Background", meta = (DisplayName = "Tile Material", EditCondition = "bCustomTileMaterial == true", EditConditionHides))
	UMaterial* TileMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Animations", meta = (DisplayName = "Has Hover Animation"))
	bool bOnHoverAnimation;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "On Hover Animation", EditCondition = "bOnHoverAnimation == true", BindWidgetAnim, EditConditionHides))
	TObjectPtr<UWidgetAnimation> OnHoverAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Animations", meta = (DisplayName = "Has Un Hover Animation"))
	bool bOnUnHoverAnimation;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = " Un Hover Animation", EditCondition = "bOnUnHoverAnimation == true", BindWidgetAnim, EditConditionHides))
	TObjectPtr<UWidgetAnimation> UnHoverAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Animations", meta = (DisplayName = "Has Press Animation"))
	bool bOnPressAnimation;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "Press Animation", EditCondition = "bOnPressAnimation == true", BindWidgetAnim, EditConditionHides))
	TObjectPtr<UWidgetAnimation> PressAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Animations", meta = (DisplayName = "Has Release Animation"))
	bool bOnReleaseAnimation;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "Release Animation", EditCondition = "bOnReleaseAnimation == true", BindWidgetAnim, EditConditionHides))
	TObjectPtr<UWidgetAnimation> ReleaseAnimation;

	UMaterialInstanceDynamic* MaterialInstance;
};
