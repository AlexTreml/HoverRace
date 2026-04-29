//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SettingsParamBase.generated.h"

/// <summary>
/// Settings base for params inside a game settings.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API USettingsParamBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* TitleTextBlock;

	USettingsParamBase(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	virtual void PostLoad() override;

	UFUNCTION(BlueprintSetter)
	void SetTitleText(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetTitleTextFont(FSlateFontInfo Font);

	void UpdateTextBlock();

	/*Title text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleText, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextColor, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor TitleTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTitleTextFont, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo TitleTextFont;

};
