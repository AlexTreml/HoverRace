//========= Copyright 2023 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/Texture.h"
#include "Variables.generated.h"
/**
 *
 */

/// <summary>
/// Key Binding Types (Text/Icons)
/// </summary>
UENUM(BlueprintType)
enum class EKeyBindingTypes : uint8
{
	Text = 0,
	Icons
};

/// <summary>
/// Credits skip types.
/// </summary>
UENUM(BlueprintType)
enum class ESkipTypes : uint8
{
	RemoveWidget = 0,
	ToWidget
};

/// <summary>
/// Open widget types.
/// </summary>
UENUM(BlueprintType)
enum class EOpenWidgetTypes : uint8
{
	OpenWidget = 0,
	CustomEventOnly
};

/// <summary>
/// Server info structure. Contains general information about the server.
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FServerInfo
{
	GENERATED_BODY()

	/// <summary>
	/// Server name
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	FText ServerName;

	/// <summary>
	/// Users amount on the server.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	int UsersNumber;
	
	/// <summary>
	/// Max users amount on the server.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	int MaxUsersNumber;
	
	/// <summary>
	/// Current ping value. 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	int Ping;
	
	/// <summary>
	/// IP Adress
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	FString IPAdress; 
	
	/// <summary>
	/// Other data string
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	FString OtherData;
};

/// <summary>
/// Struct used in the credits.
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FCreditSection
{
	GENERATED_BODY()

	/// <summary>
	/// Title text of the section
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText Title;

	/// <summary>
	/// Content array
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FText> LineArray;
};

/// <summary>
/// Button icon structure. Used for input settings.
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FButtonIcon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UTexture* IcoNormal = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UTexture* IcoPressed = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UTexture* IcoHovered = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UTexture* IcoDisabled = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText KeyDisplayName;
};

/// <summary>
/// Command & value. Used in a game settings to execute.
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FCommandOnValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FString Command;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	int IntSettingValue = 0; //0,1,2...
};

/// <summary>
/// Setting type
/// </summary>
UENUM(BlueprintType)
enum class ESettingType : uint8
{
	Switcher = 0,
	ComboBox,
	Slider
};

/// <summary>
/// 
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText SettingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	ESettingType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", EditCondition = "Type != ESettingType::Slider"))
	FString SettingCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", EditCondition = "Type != ESettingType::Slider"))
	TArray<FText> ValueNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", EditCondition = "Type != ESettingType::Slider"))
	TArray<FCommandOnValue> AdditionalCommandOnValue;

};

/// <summary>
/// 
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FSettingCategory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FText CategoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TArray<FSetting> Setting;
};

/// <summary>
/// 
/// </summary>
USTRUCT(BlueprintType)
struct ADVANCEDMENUSYSTEM_API FSavedSetting : public FSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	int IntValue = 0;
};