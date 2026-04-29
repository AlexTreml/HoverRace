//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/SwitchWidget.h"

USwitchWidget::USwitchWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Value = 0;
}


void USwitchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Left_Button->OnPressed.Clear();
	Left_Button->OnClicked.Clear();
	Left_Button->OnHovered.Clear();
	Left_Button->OnUnhovered.Clear();
	Left_Button->OnReleased.Clear();

	Right_Button->OnPressed.Clear();
	Right_Button->OnClicked.Clear();
	Right_Button->OnHovered.Clear();
	Right_Button->OnUnhovered.Clear();
	Right_Button->OnReleased.Clear();

	Left_Button->OnPressed.AddDynamic(this, &USwitchWidget::Left_Pressed);
	Left_Button->OnReleased.AddDynamic(this, &USwitchWidget::Left_Released);
	Left_Button->OnHovered.AddDynamic(this, &USwitchWidget::Left_Hovered);
	Left_Button->OnUnhovered.AddDynamic(this, &USwitchWidget::Left_UnHovered);
	Left_Button->OnClicked.AddDynamic(this, &USwitchWidget::Left_Clicked);

	Right_Button->OnPressed.AddDynamic(this, &USwitchWidget::Right_Pressed);
	Right_Button->OnReleased.AddDynamic(this, &USwitchWidget::Right_Released);
	Right_Button->OnHovered.AddDynamic(this, &USwitchWidget::Right_Hovered);
	Right_Button->OnUnhovered.AddDynamic(this, &USwitchWidget::Right_UnHovered);
	Right_Button->OnClicked.AddDynamic(this, &USwitchWidget::Right_Clicked);

	if (!ValueNames.Num())
	{
		CurrentValueName->SetText(FText::AsCultureInvariant("None"));
	}
	else
	{
		if (ValueNames.IsValidIndex(0))
		{
			CurrentValueName->SetText(ValueNames[0]);
		}
		else
		{
			CurrentValueName->SetText(FText::AsCultureInvariant("None"));
		}
	}

}

void USwitchWidget::Left_Pressed()
{
	OnLeftPressed.Broadcast();

	if (ValueNames.Num())
	{
		if (Value > 0) 
		{
			--Value;

			if (ValueNames.IsValidIndex(Value))
			{
				CurrentValueName->SetText(ValueNames[Value]);
			}

			OnValueChanged(Value);
		}
	}
}

void USwitchWidget::Left_Clicked()
{
	OnLeftClicked.Broadcast();
}

void USwitchWidget::Left_Released()
{
	OnLeftReleased.Broadcast();
}

void USwitchWidget::Left_Hovered()
{
	OnLeftHovered.Broadcast();
}

void USwitchWidget::Left_UnHovered()
{
	OnLeftUnHovered.Broadcast();
}

void USwitchWidget::Right_Pressed()
{
	OnRightPressed.Broadcast();

	if (ValueNames.Num())
	{
		if (Value < ValueNames.Num() - 1)
		{
			++Value;

			if (ValueNames.IsValidIndex(Value))
			{
				CurrentValueName->SetText(ValueNames[Value]);
			}

			OnValueChanged(Value);
		}
	}
}

void USwitchWidget::Right_Clicked()
{
	OnRightClicked.Broadcast();
}

void USwitchWidget::Right_Released()
{
	OnRightReleased.Broadcast();
}

void USwitchWidget::Right_Hovered()
{
	OnRightHovered.Broadcast();
}

void USwitchWidget::Right_UnHovered()
{
	OnRightUnHovered.Broadcast();
}

void USwitchWidget::OnValueChanged(int NewValue)
{
	OnValueChangedV(NewValue);

	OnSwitchChange.Broadcast(NewValue);
}

void USwitchWidget::OnValueChangedV(int NewValue)
{

}

void USwitchWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USwitchWidget::UpdateValueName()
{
	if (ValueNames.IsValidIndex(Value))
	{
		CurrentValueName->SetText(ValueNames[Value]);
	}
}