//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/CompasWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Materials/MaterialInstanceDynamic.h"

UCompasWidget::UCompasWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{

	}
}


void UCompasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MaterialInstance)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(CompasMaterial, this);

		if (MaterialInstance)
		{
			CompasImage->SetBrushFromMaterial(MaterialInstance);
		}
	}

}

void UCompasWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	SetDirection();

}

void UCompasWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// We get the GCWidget directly because MyWidget could be the fullscreen host widget if we've been added
	// to the viewport.
	TSharedPtr<SObjectWidget> SafeGCWidget = MyGCWidget.Pin();

	if (CompasImage)
	{
		if (!MaterialInstance)
		{
			MaterialInstance = UMaterialInstanceDynamic::Create(CompasMaterial, this);

			if (MaterialInstance)
			{
				CompasImage->SetBrushFromMaterial(MaterialInstance);
			}
		}
	}
}


TSharedRef<SWidget> UCompasWidget::RebuildWidget()
{
	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	return Widget;
}

void UCompasWidget::SetPlayerCamera(UCameraComponent* Camera)
{
	PlayerCameraComponent = Camera;
}

void UCompasWidget::SetDirection()
{
	if (PlayerCameraComponent && MaterialInstance)
	{
		//UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CompasImage);
		//FVector2D Position;

		//Position.X = (PlayerCameraComponent->GetComponentRotation().Yaw * -1.f * 10.f) - CompasHalfWidth;
		//CanvasSlot->SetPosition(Position);

		MaterialInstance->SetScalarParameterValue("Offset", PlayerCameraComponent->GetComponentRotation().Yaw / 360.f);
	}
}