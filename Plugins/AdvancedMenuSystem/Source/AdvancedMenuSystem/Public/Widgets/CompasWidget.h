//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "CompasWidget.generated.h"

/// <summary>
/// Compas widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UCompasWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UCompasWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	void SetDirection();

	/// <summary>
	/// Sets player PlayerCameraComponent.
	/// </summary>
	/// <param name="Camera"></param>
	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetPlayerCamera(UCameraComponent* Camera);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void SynchronizeProperties() override;

	/*Components*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UImage* CompasImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Compas Material", AllowPrivateAccess = "true"))
	UMaterial* CompasMaterial;

	UCameraComponent* PlayerCameraComponent;

	UMaterialInstanceDynamic* MaterialInstance;

};
