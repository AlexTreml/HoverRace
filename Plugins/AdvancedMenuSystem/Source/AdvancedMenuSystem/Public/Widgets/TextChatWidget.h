//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Widgets/TextBlockWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "TextChatWidget.generated.h"

/// <summary>
/// Game chat widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UTextChatWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UEditableTextBox* EditField;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UVerticalBox* MessagesBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* UserMessageTextPreview;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* GlobalMessageTextPreview;

	UTextChatWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	void FocusChat();

	void ExitChat();

	UFUNCTION()
	void Scroll(bool Up);

	void SetUpChatComponent();

	UFUNCTION(BlueprintCallable, Category = "Chat")
	void AddChatUserMessage(FString User,FString Message, FColor Color, FSlateFontInfo Font, bool CustomStyle = false);

	UFUNCTION(BlueprintCallable, Category = "Chat")
	void AddChatGlobalMessage(FString Message, FColor Color, FSlateFontInfo Font, bool CustomStyle = false);

	void UpdatePreviewText();

	//User message Style
	UFUNCTION(BlueprintSetter)
	void SetUserMessageTextPreview(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetUserMessageTextPreviewColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetUserMessageTextPreviewFont(FSlateFontInfo Font);

	/*Text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUserMessageTextPreview, Category = "Settings|User Message", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText UserMessagePreviewText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUserMessageTextPreviewColor, Category = "Settings|User Message", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor UserMessagePreviewTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUserMessageTextPreviewFont, Category = "Settings|User Message", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo UserMessagePreviewTextFont;

	//Global message Style
	UFUNCTION(BlueprintSetter)
	void SetGlobalMessageTextPreview(FText Text);

	UFUNCTION(BlueprintSetter)
	void SetGlobalMessageTextPreviewColor(FColor Color);

	UFUNCTION(BlueprintSetter)
	void SetGlobalMessageTextPreviewFont(FSlateFontInfo Font);

	/*Text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetGlobalMessageTextPreview, Category = "Settings|Global Message", meta = (AllowPrivateAccess = "true", DisplayName = "Text"))
	FText GlobalMessagePreviewText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetGlobalMessageTextPreviewColor, Category = "Settings|Global Message", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))
	FColor GlobalMessagePreviewTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetGlobalMessageTextPreviewFont, Category = "Settings|Global Message", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FSlateFontInfo GlobalMessagePreviewTextFont;

	UFUNCTION()
	void OnTextCommited(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(VisibleAnywhere, Category = "Chat")
	bool bChatFocused;

	bool bLocalPlayer;

protected:

	virtual void SynchronizeProperties() override;

	virtual void NativeOnInitialized() override;

	float ScrollMultiplier;

	TArray<UTextBlockWidget*> MessagesTextBlockArr;

	UActorComponent* ParentComponent;

};
