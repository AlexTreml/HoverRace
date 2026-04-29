//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "TextBlockWidget.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDMENUSYSTEM_API UTextBlockWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UTextBlockWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintSetter)
	void SetText(FText NewText);

	UFUNCTION(BlueprintSetter)
	void SetTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetTextFont(FSlateFontInfo Font);

	void UpdateTextBlock();

	/*Text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetText, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTextColor, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor TextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTextFont, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo TextFont;

	UTextBlock* TextBlock;

protected:

	virtual void NativeOnInitialized() override;
};
