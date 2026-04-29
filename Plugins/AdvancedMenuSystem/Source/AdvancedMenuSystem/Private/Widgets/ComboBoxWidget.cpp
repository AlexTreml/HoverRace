//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#include "Widgets/ComboBoxWidget.h"

UComboBoxWidget::UComboBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UComboBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ComboBoxString->OnSelectionChanged.Clear();

	ComboBoxString->OnSelectionChanged.AddDynamic(this, &UComboBoxWidget::OnComboBoxItemChange);
}

void UComboBoxWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdateComboBox();
}

void UComboBoxWidget::UpdateComboBox()
{
	if (ComboBoxString)
	{
		ComboBoxString->SetItemStyle(ComboBoxStyle);

		//ComboBoxString->ClearSelection();
		ComboBoxString->ClearOptions();

		for (int i = 0; i < Options.Num(); i++)
		{
			ComboBoxString->AddOption(Options[i]);
		}

		ComboBoxString->SetSelectedOption(DefaultOption);
	}
}

void UComboBoxWidget::SetSelectedOption(FString OptionName)
{
	ComboBoxString->SetSelectedOption(OptionName);
}

void UComboBoxWidget::SetSelectedIndex(int Index)
{
	ComboBoxString->SetSelectedIndex(Index);
}

void UComboBoxWidget::SetComboBoxStyle(FTableRowStyle Style)
{
	ComboBoxString->SetItemStyle(Style);
}

void UComboBoxWidget::OnComboBoxItemChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnSelectionChanged.Broadcast(SelectedItem, SelectionType);
}