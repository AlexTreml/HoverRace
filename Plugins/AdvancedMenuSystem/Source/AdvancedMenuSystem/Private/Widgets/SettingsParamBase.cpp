//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/SettingsParamBase.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

USettingsParamBase::USettingsParamBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

void USettingsParamBase::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateTextBlock();
}

void USettingsParamBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdateTextBlock();

}

void USettingsParamBase::PostLoad()
{
	Super::PostLoad();

	UpdateTextBlock();
}

void USettingsParamBase::SetTitleText(FText Text)
{
	TitleText = Text;

	UpdateTextBlock();
}

void USettingsParamBase::SetTitleTextColor(FColor Color)
{
	TitleTextColor = Color;

	UpdateTextBlock();
}

void USettingsParamBase::SetTitleTextFont(FSlateFontInfo Font)
{
	TitleTextFont = Font;

	UpdateTextBlock();
}

void USettingsParamBase::UpdateTextBlock()
{
	if (TitleTextBlock)
	{
		TitleTextBlock->SetText(TitleText);
		TitleTextBlock->SetColorAndOpacity(TitleTextColor);
		TitleTextBlock->SetFont(TitleTextFont);
	}
}