//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/TileWidget.h"
#include "Engine/Font.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

UTileWidget::UTileWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> TileMat(TEXT("Material'/AdvancedMenuSystem/Demo/Materials/M_Tile.M_Tile'"));

		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		TitleTextFont = DefaultFont;
		DescriptionTextFont = DefaultFont;

		if (TileMat.Succeeded())
		{
			TileMaterial = TileMat.Object;

			FButtonStyle ButtonStyle;
			FSlateBrush Brush;
			Brush.SetResourceObject(TileMaterial);
			Brush.ImageType = ESlateBrushImageType::Vector;
			Brush.DrawAs = ESlateBrushDrawType::Image;
			ButtonStyle.SetNormal(Brush);
			ButtonStyle.SetPressed(Brush);
			ButtonStyle.SetHovered(Brush);

			if (Button)
			{
				Button->SetStyle(ButtonStyle);
			}
		}
	}

	TitleText = FText::AsCultureInvariant("Title");
	TitleTextColor = FColor(255,255,255);

	DescriptionText = FText::AsCultureInvariant("Description");
	DescriptionTextColor = FColor(255, 255, 255);

	bTintTile = false;
	TintColor = FColor(0, 0, 0, 255);
	TintIntensivity = 10.f;
	TileColor = FColor(255, 127, 0, 255);
	TileDimentions = FVector2D(0.9f,0.9f);
	CornerRadius = 0.1f;
	GradientFadeIntensivity = 1.f;
	BackgroundOpacity = 1.f;
}


void UTileWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnPressed.Clear();
		Button->OnHovered.Clear();
		Button->OnReleased.Clear();
		Button->OnUnhovered.Clear();

		Button->OnPressed.AddDynamic(this, &UTileWidget::DoOnPressed);
		Button->OnHovered.AddDynamic(this, &UTileWidget::DoOnHovered);
		Button->OnReleased.AddDynamic(this, &UTileWidget::DoOnReleased);
		Button->OnUnhovered.AddDynamic(this, &UTileWidget::DoOnUnHovered);
	}
}

void UTileWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// We get the GCWidget directly because MyWidget could be the fullscreen host widget if we've been added
	// to the viewport.
	TSharedPtr<SObjectWidget> SafeGCWidget = MyGCWidget.Pin();

	UpdateTextBlock();

	UpdateDescriptionTextBlock();

	if (Button)
	{
		if (!MaterialInstance)
		{
			MaterialInstance = UMaterialInstanceDynamic::Create(TileMaterial, this);

			FButtonStyle ButtonStyle;
			FSlateBrush Brush;
			Brush.SetResourceObject(MaterialInstance);
			ButtonStyle.SetNormal(Brush);
			ButtonStyle.SetPressed(Brush);
			ButtonStyle.SetHovered(Brush);
			Button->SetStyle(ButtonStyle);
		}

		if (MaterialInstance)
		{
			/*Tile General Settings*/
			UpdateTileGeneralValues();

			/*Tile Background*/
			UpdateBackgroundImageValues();

			/*Tile Background - Gradient Fade */
			UpdateGradientFadeValues();

			/*Tile Tint*/
			UpdateTileTintValues();

		}
	}
}

void UTileWidget::DoOnPressed()
{
	if (bOnPressAnimation && PressAnimation)
	{
		PlayAnimation(PressAnimation);
	}

	DoOnButtonPressed.Broadcast();
}

void UTileWidget::DoOnHovered()
{
	if (bOnHoverAnimation && OnHoverAnimation)
	{
		PlayAnimation(OnHoverAnimation);
	}

	DoOnButtonHovered.Broadcast();
}

void UTileWidget::DoOnReleased()
{
	if (bOnReleaseAnimation && ReleaseAnimation)
	{
		PlayAnimation(ReleaseAnimation);
	}

	DoOnButtonReleased.Broadcast(); 
}

void UTileWidget::DoOnUnHovered()
{
	if (bOnUnHoverAnimation && UnHoverAnimation)
	{
		PlayAnimation(UnHoverAnimation);
	}

	DoOnButtonUnHovered.Broadcast();
}

TSharedRef<SWidget> UTileWidget::RebuildWidget()
{
	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	return Widget;
}

void UTileWidget::SetTintTile(bool Value)
{
	bTintTile = Value;

	UpdateTileTintValues();
}

void UTileWidget::SetUseBackgroundImage(bool Value)
{
	bBackgroundImage = Value;

	UpdateBackgroundImageValues();
}

void UTileWidget::SetUseGradientFade(bool Value)
{
	bGradientFade = Value;

	UpdateGradientFadeValues();
}

void UTileWidget::SetGradientFadeIntensivity(float Value)
{
	GradientFadeIntensivity = Value;

	UpdateGradientFadeValues();
}

void UTileWidget::SetTintColor(FColor Value)
{
	TintColor = Value;

	UpdateGradientFadeValues();
}

void UTileWidget::SetTileColor(FColor Value)
{
	TileColor = Value;

	UpdateBackgroundImageValues();
}

void UTileWidget::SetTileImage(UTexture* Image)
{
	TileImage = Image;

	UpdateBackgroundImageValues();
}

void UTileWidget::SetTileDimentions(FVector2D Dimentions)
{
	TileDimentions = Dimentions;

	UpdateTileGeneralValues();
}

void UTileWidget::SetCornerRadius(float Value)
{
	CornerRadius = Value;

	UpdateTileGeneralValues();
}

void UTileWidget::SetSharpness(float Value)
{
	Sharpness = Value;

	UpdateTileGeneralValues();
}

void UTileWidget::SetTintIntensivity(float Value)
{
	TintIntensivity = Value;

	UpdateTileTintValues();
}

void UTileWidget::SetUseCustomTileMaterial(bool Value)
{
	bCustomTileMaterial = Value;

	//Put something here...
}

void UTileWidget::SetBackgroundOpacity(float Value)
{
	BackgroundOpacity = Value;

	UpdateBackgroundImageValues();
}

void UTileWidget::SetTileMaterial(UMaterial* Material)
{
	TileMaterial = Material;

	MaterialInstance = UMaterialInstanceDynamic::Create(TileMaterial, this);

	FButtonStyle ButtonStyle;
	FSlateBrush Brush;
	Brush.SetResourceObject(MaterialInstance);
	ButtonStyle.SetNormal(Brush);
	ButtonStyle.SetPressed(Brush);
	ButtonStyle.SetHovered(Brush);
	Button->SetStyle(ButtonStyle);
}

void UTileWidget::UpdateTileGeneralValues()
{
	MaterialInstance->SetVectorParameterValue("Tile Dimensions", FLinearColor(TileDimentions.X, TileDimentions.Y, 0.f));
	MaterialInstance->SetScalarParameterValue("CornerRadius", CornerRadius);
	MaterialInstance->SetScalarParameterValue("Sharpness", Sharpness);
}

void UTileWidget::UpdateTileTintValues()
{
	if (MaterialInstance)
	{
		if (bTintTile)
		{
			MaterialInstance->SetScalarParameterValue("Tint", 1.f);
		}
		else
		{
			MaterialInstance->SetScalarParameterValue("Tint", 0.f);
		}

		MaterialInstance->SetVectorParameterValue("Tint Color", FLinearColor(TintColor.R, TintColor.G, TintColor.B, TintColor.A));
		MaterialInstance->SetScalarParameterValue("Tint Intensivity", TintIntensivity);
	}
}

void UTileWidget::UpdateBackgroundImageValues()
{
	if (MaterialInstance)
	{
		if (bBackgroundImage)
		{
			MaterialInstance->SetScalarParameterValue("Image", 1.f);
		}
		else
		{
			MaterialInstance->SetScalarParameterValue("Image", 0.f);
		}

		MaterialInstance->SetVectorParameterValue("Color", FLinearColor(TileColor.R, TileColor.G, TileColor.B, TileColor.A));

		if (TileImage)
		{
			MaterialInstance->SetTextureParameterValue("Background", TileImage);
		}

		MaterialInstance->SetScalarParameterValue("Background Opacity", BackgroundOpacity);
	}
}

void UTileWidget::UpdateGradientFadeValues()
{
	if (MaterialInstance)
	{
		if (bGradientFade) //Gradient Fade. Can be used for the text highlight
		{
			MaterialInstance->SetScalarParameterValue("Gradient Fade", 1.f);
		}
		else
		{
			MaterialInstance->SetScalarParameterValue("Gradient Fade", 0.f);
		}

		MaterialInstance->SetScalarParameterValue("Gradient Intensivity", GradientFadeIntensivity);
	}
}

void UTileWidget::UpdateTextBlock()
{
	if (TitleTextBlock)
	{
		TitleTextBlock->SetText(TitleText);
		TitleTextBlock->SetColorAndOpacity(TitleTextColor);
		TitleTextBlock->SetFont(TitleTextFont);
	}
}

void UTileWidget::UpdateDescriptionTextBlock()
{
	if (DescriptionTextBlock)
	{
		DescriptionTextBlock->SetText(DescriptionText);
		DescriptionTextBlock->SetColorAndOpacity(DescriptionTextColor);
		DescriptionTextBlock->SetFont(DescriptionTextFont);
	}
}

void UTileWidget::SetTitleText(FText Text)
{
	TitleText = Text;

	UpdateTextBlock();
}

void UTileWidget::SetTitleTextColor(FColor Color)
{
	TitleTextColor = Color;

	UpdateTextBlock();
}

void UTileWidget::SetTitleTextFont(FSlateFontInfo Font)
{
	TitleTextFont = Font;

	UpdateTextBlock();
}

void UTileWidget::SetDescriptionText(FText Text)
{
	DescriptionText = Text;

	UpdateDescriptionTextBlock();
}

void UTileWidget::SetDescriptionTextColor(FColor Color)
{
	DescriptionTextColor = Color;

	UpdateDescriptionTextBlock();
}

void UTileWidget::SetDescriptionTextFont(FSlateFontInfo Font)
{
	DescriptionTextFont = Font;

	UpdateDescriptionTextBlock();
}