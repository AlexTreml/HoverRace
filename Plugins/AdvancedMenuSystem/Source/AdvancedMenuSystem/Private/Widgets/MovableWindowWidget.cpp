//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/MovableWindowWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

UMovableWindowWidget::UMovableWindowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> TileMat(TEXT("Material'/AdvancedMenuSystem/Demo/Materials/M_Tile.M_Tile'"));

		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		WindowTitleTextFont = DefaultFont;
	}

	WindowTitleText = FText::AsCultureInvariant("WINDOW TITLE");
	WindowTitleTextColor = FColor(255, 255, 255);
}

void UMovableWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HeaderWidget)
	{
		HeaderWidget->DoOnButtonPressed.Clear();
		HeaderWidget->DoOnButtonReleased.Clear();

		HeaderWidget->DoOnButtonPressed.AddDynamic(this, &UMovableWindowWidget::DoOnDrag);
		HeaderWidget->DoOnButtonReleased.AddDynamic(this, &UMovableWindowWidget::DoOnReleasedDrag);
	}
}

void UMovableWindowWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	//Window Title
	SetWindowTitleText(WindowTitleText);
	SetWindowTitleTextColor(WindowTitleTextColor);
	SetWindowTitleTextFont(WindowTitleTextFont);
}

void UMovableWindowWidget::PostLoad()
{
	Super::PostLoad();

}

void UMovableWindowWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	if(bIsDraging)
	{
		UpdateWindowLocation();
	}
}

void UMovableWindowWidget::DoOnDrag()
{
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	if (CanvasSlot)
	{
		PositionDiff = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) - CanvasSlot->GetPosition();

		bIsDraging = true;
	}
}

void UMovableWindowWidget::DoOnReleasedDrag()
{
	UpdateWindowLocationStop();
}

void UMovableWindowWidget::UpdateWindowLocation()
{
	MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	CanvasSlot->SetPosition(MousePosition - PositionDiff);
}

void UMovableWindowWidget::UpdateWindowLocationStop()
{
	bIsDraging = false;
}

void UMovableWindowWidget::SetWindowTitleText(FText Text)
{
	WindowTitleText = Text;

	UpdateWindowText();
}

void UMovableWindowWidget::SetWindowTitleTextColor(FColor Color)
{
	WindowTitleTextColor = Color;

	UpdateWindowText();
}

void UMovableWindowWidget::SetWindowTitleTextFont(FSlateFontInfo Font)
{
	WindowTitleTextFont = Font;

	UpdateWindowText();
}

void UMovableWindowWidget::UpdateWindowText()
{
	if (HeaderWidget)
	{
		HeaderWidget->SetTitleText(WindowTitleText);
		HeaderWidget->SetTitleTextColor(WindowTitleTextColor);
		HeaderWidget->SetTitleTextFont(WindowTitleTextFont);
	}
}