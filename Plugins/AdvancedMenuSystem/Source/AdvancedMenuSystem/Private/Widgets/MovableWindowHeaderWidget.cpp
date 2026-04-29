//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#include "Widgets/MovableWindowHeaderWidget.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

UMovableWindowHeaderWidget::UMovableWindowHeaderWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> TileMat(TEXT("Material'/AdvancedMenuSystem/Demo/Materials/M_Tile.M_Tile'"));

		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		TitleTextFont = DefaultFont;
	}

	TitleText = FText::AsCultureInvariant("Title");
	TitleTextColor = FColor(255, 255, 255);
}

void UMovableWindowHeaderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateTextBlock();

	if (HeaderButton)
	{
		HeaderButton->OnPressed.Clear();
		HeaderButton->OnHovered.Clear();
		HeaderButton->OnReleased.Clear();
		HeaderButton->OnUnhovered.Clear();

		HeaderButton->OnPressed.AddDynamic(this, &UMovableWindowHeaderWidget::DoOnPressed);
		HeaderButton->OnHovered.AddDynamic(this, &UMovableWindowHeaderWidget::DoOnHovered);
		HeaderButton->OnReleased.AddDynamic(this, &UMovableWindowHeaderWidget::DoOnReleased);
		HeaderButton->OnUnhovered.AddDynamic(this, &UMovableWindowHeaderWidget::DoOnUnHovered);
	}
}

void UMovableWindowHeaderWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdateTextBlock();

}

void UMovableWindowHeaderWidget::PostLoad()
{
	Super::PostLoad();

	UpdateTextBlock();
}

void UMovableWindowHeaderWidget::SetTitleText(FText Text)
{
	TitleText = Text;

	UpdateTextBlock();
}

void UMovableWindowHeaderWidget::SetTitleTextColor(FColor Color)
{
	TitleTextColor = Color;

	UpdateTextBlock();
}

void UMovableWindowHeaderWidget::SetTitleTextFont(FSlateFontInfo Font)
{
	TitleTextFont = Font;

	UpdateTextBlock();
}

void UMovableWindowHeaderWidget::UpdateTextBlock()
{
	if (TitleTextBlock)
	{
		TitleTextBlock->SetText(TitleText);
		TitleTextBlock->SetColorAndOpacity(TitleTextColor);
		TitleTextBlock->SetFont(TitleTextFont);
	}
}

void UMovableWindowHeaderWidget::DoOnPressed()
{
	DoOnButtonPressed.Broadcast();
}

void UMovableWindowHeaderWidget::DoOnHovered()
{
	DoOnButtonHovered.Broadcast();
}

void UMovableWindowHeaderWidget::DoOnReleased()
{
	DoOnButtonReleased.Broadcast();
}

void UMovableWindowHeaderWidget::DoOnUnHovered()
{
	DoOnButtonUnHovered.Broadcast();
}