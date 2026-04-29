//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "IntroWidget.generated.h"

/// <summary>
/// Intro screen widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UIntroWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoOnIntroEnd);

public:

	UIntroWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	/// <summary>
	/// Start Logo Showcase
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Logo Showcase")
	void StartLogoShowcase();

	/// <summary>
	/// Is the intro finished or not.
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE bool IsFinished() const { return IntroFinished; };

	/////Window Change

	UPROPERTY(BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UCommonActivatableWidgetContainerBase* ActivatableWidget;

	TSubclassOf<UCommonActivatableWidget> MainMenuWidget;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDoOnIntroEnd DoOnIntroEnd;

protected:

	/// <summary>
	/// Updates the bottom text.
	/// </summary>
	void UpdateBottomTextBlock();

	/// <summary>
	/// Proces each logo.
	/// </summary>
	/// <param name="i"></param>
	void ProcedAllLogos(int i);

	//virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void SynchronizeProperties() override;

	/// <summary>
	/// Logo to change.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UImage* LogoImage;

	/// <summary>
	/// Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidgetOptional))
	class UTextBlock* BottomTextBlock;

	/// <summary>
	/// Background.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UImage* BackgroundImage;

	/// <summary>
	/// Logo Images Array.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Logo", meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> LogoImages;

	/// <summary>
	/// Start showcase on spawn.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Logo", meta = (AllowPrivateAccess = "true"))
	bool bStartOnSpawn;

	/// <summary>
	/// Logo Show Time.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Logo", meta = (AllowPrivateAccess = "true"))
	float LogoShowTime;

	/// <summary>
	/// Logo change delay.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Logo", meta = (AllowPrivateAccess = "true"))
	float LogoChangeDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Logo", meta = (AllowPrivateAccess = "true"))
	float EndChangeTime;

	/// <summary>
	/// Fade speed. Default is 1.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Logo", meta = (AllowPrivateAccess = "true"))
	float FadeSpeed;

	/// <summary>
	/// Text of the Bottom Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Text", meta = (AllowPrivateAccess = "true"))
	FText BottomText;
	
	/// <summary>
	/// Color of the Bottom Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor BottomTextColor;

	/// <summary>
	/// Font of the Bottom Text Block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Title", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo BottomTextFont;

	/// <summary>
	/// Fade Animation of the logo image.
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "Logo Fade Animation", BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> LogoFadeAnimation;

	/// <summary>
	/// Will do background fade on end or not.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Animations", meta = (DisplayName = "Use Background Fade"))
	bool bUseBackgroundFade;

	/// <summary>
	/// Background fade animation
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Settings|Animations", meta = (DisplayName = "Background Fade Animation", BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> BackgroundFadeAnimation;

	/// <summary>
	/// Whether or not intro is finished.
	/// </summary>
	bool IntroFinished;

	/// <summary>
	/// Number of the showed logos.
	/// </summary>
	int ShowedLogos;

	void CheckEndIntroWindowChange();

private:

	FTimerHandle handle;

	FTimerHandle HandleLoop;

};
