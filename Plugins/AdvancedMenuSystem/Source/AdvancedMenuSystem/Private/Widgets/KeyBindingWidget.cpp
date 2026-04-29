//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/KeyBindingWidget.h"
#include "Styling/DefaultStyleCache.h"
#include "Engine/Font.h"

UKeyBindingWidget::UKeyBindingWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
		WidgetButtonStyle = UE::Slate::Private::FDefaultStyleCache::GetRuntime().GetButtonStyle();
	TextStyle = UE::Slate::Private::FDefaultStyleCache::GetRuntime().GetTextBlockStyle();

#if WITH_EDITOR 
	if (IsEditorWidget())
	{
		WidgetButtonStyle = UE::Slate::Private::FDefaultStyleCache::GetEditor().GetButtonStyle();
		TextStyle = UE::Slate::Private::FDefaultStyleCache::GetEditor().GetTextBlockStyle();

		// The CDO isn't an editor widget and thus won't use the editor style, call post edit change to mark difference from CDO
		PostEditChange();
	}
#endif // WITH_EDITOR

	KeySelectionText = NSLOCTEXT("InputKeySelector", "DefaultKeySelectionText", "...");
	NoKeySpecifiedText = NSLOCTEXT("InputKeySelector", "DefaultEmptyText", "Empty");
	SelectedKey = FInputChord(EKeys::Invalid);
	bAllowModifierKeys = true;
	bAllowGamepadKeys = false;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
		EscapeKeys.AddUnique(EKeys::Gamepad_Special_Right); // In most (if not all) cases this is going to be the menu button

	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
			TextStyle.Font = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));
		PRAGMA_ENABLE_DEPRECATION_WARNINGS
	}
}

void UKeyBindingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InputKeySelector->OnKeySelected.Clear();
	InputKeySelector->OnIsSelectingKeyChanged.Clear();

	InputKeySelector->OnKeySelected.AddDynamic(this, &UKeyBindingWidget::KeySelected);
	InputKeySelector->OnIsSelectingKeyChanged.AddDynamic(this, &UKeyBindingWidget::IsSelectingKeyChanged);
}

void UKeyBindingWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (InputKeySelector)
	{
		SetSelectedKey(SelectedKey);
		SetKeySelectionText(KeySelectionText);
		SetNoKeySpecifiedText(NoKeySpecifiedText);
		SetAllowModifierKeys(bAllowModifierKeys);
		SetAllowGamepadKeys(bAllowGamepadKeys);
		SetAllowGamepadKeys(bAllowGamepadKeys);
		SetButtonStyle(WidgetButtonStyle);
		SetTextStyle(TextStyle);
		SetMargin(Margin);
		SetEscapeKeys(EscapeKeys);
	}
}

void UKeyBindingWidget::CheckInputType()
{

}

void UKeyBindingWidget::KeySelected(FInputChord Key)
{
	UpdateIcon(Key);

	SelectedKey = Key;

	OnKeySelected.Broadcast(Key);
}

void UKeyBindingWidget::UpdateIcon(FInputChord Key)
{
	if (KeyBindingType != EKeyBindingTypes::Text)
	{
		TextStyle.ColorAndOpacity = FSlateColor(FColor(255.f, 255.f, 255.f, 0.f));

		if (!ButtonIcons.IsEmpty())
		{
			int index = 0;

			for (int i = 0; i < ButtonIcons.Num(); i++)
			{
				if (Key.Key.GetDisplayName().ToString() == ButtonIcons[i].KeyDisplayName.ToString())
				{
					index = i;

					break;
				}
			}

			if (ButtonIcons.IsValidIndex(index))
			{
				if (ButtonIcons[index].IcoNormal)
				{
					WidgetButtonStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
					WidgetButtonStyle.Normal.SetResourceObject(ButtonIcons[index].IcoNormal);

					WidgetButtonStyle.Normal.TintColor = FSlateColor(FColor(255.f, 255.f, 255.f, 255.f));
				}

				if (ButtonIcons[index].IcoPressed)
				{
					WidgetButtonStyle.Pressed.DrawAs = ESlateBrushDrawType::Image;
					WidgetButtonStyle.Pressed.SetResourceObject(ButtonIcons[index].IcoPressed);

					WidgetButtonStyle.Pressed.TintColor = FSlateColor(FColor(255.f, 255.f, 255.f, 255.f));
				}

				if (ButtonIcons[index].IcoHovered)
				{
					WidgetButtonStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;
					WidgetButtonStyle.Hovered.SetResourceObject(ButtonIcons[index].IcoHovered);

					WidgetButtonStyle.Hovered.TintColor = FSlateColor(FColor(255.f, 255.f, 255.f, 255.f));
				}

				if (ButtonIcons[index].IcoDisabled)
				{
					WidgetButtonStyle.Disabled.DrawAs = ESlateBrushDrawType::Image;
					WidgetButtonStyle.Disabled.SetResourceObject(ButtonIcons[index].IcoDisabled);

					WidgetButtonStyle.Disabled.TintColor = FSlateColor(FColor(255.f, 255.f, 255.f, 255.f));
				}

				SetButtonStyle(WidgetButtonStyle);

			}
		}
	}
}

void UKeyBindingWidget::IsSelectingKeyChanged()
{
	OnIsSelectingKeyChanged.Broadcast();
}

void UKeyBindingWidget::SetSelectedKey(const FInputChord& InSelectedKey)
{
	SelectedKey = InSelectedKey;
	InputKeySelector->SetSelectedKey(InSelectedKey);
	
}

FInputChord UKeyBindingWidget::GetSelectedKey() const
{
	return InputKeySelector->GetSelectedKey();
}

void UKeyBindingWidget::SetKeySelectionText(FText InKeySelectionText)
{
	KeySelectionText = InKeySelectionText;

	if (InputKeySelector)
	{
		InputKeySelector->SetKeySelectionText(InKeySelectionText);
	}
}

const FText& UKeyBindingWidget::GetKeySelectionText() const
{
	return KeySelectionText;
}

void UKeyBindingWidget::SetNoKeySpecifiedText(FText InNoKeySpecifiedText)
{
	NoKeySpecifiedText = InNoKeySpecifiedText;

	if (InputKeySelector)
	{
		InputKeySelector->SetNoKeySpecifiedText(InNoKeySpecifiedText);
	}
}

const FText& UKeyBindingWidget::GetNoKeySpecifiedText() const
{
	return NoKeySpecifiedText;
}

void UKeyBindingWidget::SetAllowModifierKeys(bool bInAllowModifierKeys)
{
	bAllowModifierKeys = bInAllowModifierKeys;

	if (InputKeySelector)
	{
		InputKeySelector->SetAllowModifierKeys(bInAllowModifierKeys);
	}
}

bool UKeyBindingWidget::AllowModifierKeys() const
{
	return bAllowModifierKeys;
}

void UKeyBindingWidget::SetAllowGamepadKeys(bool bInAllowGamepadKeys)
{
	bAllowGamepadKeys = bInAllowGamepadKeys;

	if (InputKeySelector)
	{
		InputKeySelector->SetAllowGamepadKeys(bInAllowGamepadKeys);
	}
}

bool UKeyBindingWidget::AllowGamepadKeys() const
{
	return bAllowGamepadKeys;
}

bool UKeyBindingWidget::GetIsSelectingKey() const
{
	if (InputKeySelector)
	{
		return InputKeySelector->GetIsSelectingKey();
	}
	else
	{
		return false;
	}
}

void UKeyBindingWidget::SetSelectionBlockVisibility(const ESlateVisibility InVisibility)
{
	if (InputKeySelector)
	{
		InputKeySelector->SetTextBlockVisibility(InVisibility);
	}
}

void UKeyBindingWidget::SetButtonStyle(const FButtonStyle& ButtonStyle)
{
	WidgetButtonStyle = ButtonStyle;
	if (InputKeySelector)
	{
		InputKeySelector->SetButtonStyle(ButtonStyle);
	}
}

void UKeyBindingWidget::SetButtonStyle(const FButtonStyle* ButtonStyle)
{
	WidgetButtonStyle = *ButtonStyle;
	if (InputKeySelector)
	{
		InputKeySelector->SetButtonStyle(*ButtonStyle);
	}
}

const FButtonStyle& UKeyBindingWidget::GetButtonStyle() const
{
	return WidgetButtonStyle;
}

void UKeyBindingWidget::SetTextStyle(const FTextBlockStyle& InTextStyle)
{
	TextStyle = InTextStyle;

	if (InputKeySelector)
	{
		InputKeySelector->SetTextStyle(InTextStyle);
	}
}

const FTextBlockStyle& UKeyBindingWidget::GetTextStyle() const
{
	return TextStyle;
}

void UKeyBindingWidget::SetMargin(const FMargin& InMargin)
{
	Margin = InMargin;
	if (InputKeySelector)
	{
		InputKeySelector->SetMargin(InMargin);
	}
}

const FMargin& UKeyBindingWidget::GetMargin() const
{
	return Margin;
}

void UKeyBindingWidget::SetEscapeKeys(const TArray<FKey>& InKeys)
{
	EscapeKeys = InKeys;

	if (InputKeySelector)
	{
		InputKeySelector->SetEscapeKeys(InKeys);
	}
}