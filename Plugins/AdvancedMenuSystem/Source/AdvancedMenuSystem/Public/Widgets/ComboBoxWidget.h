//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/SettingsParamBase.h"
#include "Components/ComboBoxString.h"
#include "ComboBoxWidget.generated.h"

/// <summary>
/// Combo box setting param widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UComboBoxWidget : public USettingsParamBase
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedEvent, FString, SelectedItem, ESelectInfo::Type, SelectionType);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UComboBoxString* ComboBoxString;

	UComboBoxWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSelectedOption(FString OptionName);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetComboBoxStyle(FTableRowStyle Style);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetSelectedIndex(int Index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetComboBoxStyle, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Font"))
	FTableRowStyle ComboBoxStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FString> Options;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FString DefaultOption;

	/** Called when a new item is selected in the combobox. */
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnSelectionChangedEvent OnSelectionChanged;

	/// <summary>
	/// Set values to the ComboBoxString.
	/// </summary>
	virtual void UpdateComboBox();

protected:

	UFUNCTION()
	void OnComboBoxItemChange(FString SelectedItem, ESelectInfo::Type SelectionType);

};
