//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Widgets/MovableWindowHeaderWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "MovableWindowWidget.generated.h"

/// <summary>
/// Movable window widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UMovableWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UMovableWindowWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	virtual void PostLoad() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void DoOnDrag();

	UFUNCTION()
	void DoOnReleasedDrag();

	void UpdateWindowLocation();

	void UpdateWindowLocationStop();

	/*Components*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UMovableWindowHeaderWidget* HeaderWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UCanvasPanel* WindowCanvasPanel;

	UFUNCTION(BlueprintSetter)
	void SetWindowTitleText(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetWindowTitleTextColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetWindowTitleTextFont(FSlateFontInfo Font);

	void UpdateWindowText();

	/*Title text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetWindowTitleText, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText WindowTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetWindowTitleTextColor, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor WindowTitleTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetWindowTitleTextFont, Category = "Settings|Title Text", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo WindowTitleTextFont;

private:

	bool bIsDraging;

	FVector2D MousePosition;

	FVector2D PositionDiff;

};
