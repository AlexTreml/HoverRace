//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "CommonActivatableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveFloat.h"
#include "LoadingScreenWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FComponentValueChange, ULoadingScreenWidget, OnValueChange, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnLoadStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnLoadEnd);

/// <summary>
/// Loading screen widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API ULoadingScreenWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	ULoadingScreenWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void StartLoad();

	virtual void ProgressLoad(float Value);

	virtual void EndtLoad();

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UProgressBar* ProgressBar;

	/*Settings*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bUseAutoProgress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|AutoProgress", meta = (EditCondition = "bUseAutoProgress == true", EditConditionHides))
	bool bRunProgressOnStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	FProgressBarStyle WidgetStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	float Percent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EProgressBarFillType::Type> BarFillType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EProgressBarFillStyle::Type> BarFillStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	bool bIsMarquee;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	FVector2D BorderPadding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	FLinearColor FillColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|ProgressBar", meta = (AllowPrivateAccess = "true"))
	FGetLinearColor FillColorAndOpacityDelegate;

	UPROPERTY(EditAnywhere,BlueprintAssignable, Category = "Event")
	FComponentValueChange OnValueChange;

	UPROPERTY(EditAnywhere,BlueprintAssignable, Category = "Event")
	FDoOnLoadStart DoOnLoadStart;

	UPROPERTY(EditAnywhere,BlueprintAssignable, Category = "Event")
	FDoOnLoadEnd DoOnLoadEnd;

	bool bStarted;

	bool bFinished;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> AutoLoadingAnimation;

protected:


};
