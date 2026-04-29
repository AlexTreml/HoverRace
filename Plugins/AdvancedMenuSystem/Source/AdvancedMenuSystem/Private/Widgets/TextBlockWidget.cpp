//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/TextBlockWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

UTextBlockWidget::UTextBlockWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> TileMat(TEXT("Material'/AdvancedMenuSystem/Demo/Materials/M_Tile.M_Tile'"));

		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		TextFont = DefaultFont;
	}

	Text = FText::AsCultureInvariant("Text");
	TextColor = FColor(255, 255, 255);
}


void UTextBlockWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (auto RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootWidget")))
	{
		TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TextBlock"));

		if (TextBlock)
		{
			UpdateTextBlock();

			if (const auto RootWidgetSlot = RootWidget->AddChildToCanvas(TextBlock))
			{
				RootWidgetSlot->SetAutoSize(true);
				RootWidgetSlot->SetAnchors(FAnchors(0,0,1,1)); RootWidgetSlot->SetOffsets(FMargin(0,0));
			}

			WidgetTree->RootWidget = RootWidget;
		}
	}
}

void UTextBlockWidget::SetText(FText NewText)
{
	Text = NewText;
	UpdateTextBlock();
}

void UTextBlockWidget::SetTextColor(FColor Color)
{
	TextColor = Color;
	UpdateTextBlock();
}

void UTextBlockWidget::SetTextFont(FSlateFontInfo Font)
{
	TextFont = Font;
	UpdateTextBlock();
}

void UTextBlockWidget::UpdateTextBlock()
{
	if (TextBlock)
	{
		TextBlock->SetText(Text);
		TextBlock->SetColorAndOpacity(TextColor);
		TextBlock->SetFont(TextFont);
	}
}