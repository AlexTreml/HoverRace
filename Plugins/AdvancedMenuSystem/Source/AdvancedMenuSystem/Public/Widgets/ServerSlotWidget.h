//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Save/Variables.h"
#include "ServerSlotWidget.generated.h"

/// <summary>
/// Server slot widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UServerSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinPressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinUnHoverEvent);

public:

	/// <summary>
	/// Server Name text block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* TitleTextBlock;

	/// <summary>
	/// Users amount on the server text block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* UsersTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* IPAdressTextBlock;

	/// <summary>
	/// Ping text block.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UTextBlock* PingTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* JoinButton;

	/// <summary>
	/// Ping image.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UImage* PingIco;

	UServerSlotWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	//Same as Begin Play
	virtual void NativeConstruct() override;

	/// <summary>
	/// Update the server slot data.
	/// </summary>
	/// <param name="ServerName">Server Name</param>
	/// <param name="UsersNumber">Users Number</param>
	/// <param name="MaxUsersNumber">Max Users Number</param>
	/// <param name="PingValue">Ping Value</param>
	/// <param name="IPAdress">IP Adress</param>
	/// <param name="OtherData">Other Data to store</param>
	UFUNCTION(BlueprintCallable, Category = "Update")
	void UpdateServerData(FText ServerName, int UsersNumber, int MaxUsersNumber, int PingValue, FString IPAdress, FString OtherData);

	//Functions

	/// <summary>
	/// Sets a new server name and updates the TitleTextBlock text variable.
	/// </summary>
	/// <param name="Text">New Server Name</param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetServerNameText(FText Text);

	/// <summary>
	/// Sets a new color to the server name and updates the TitleTextBlock color variable.
	/// </summary>
	/// <param name="Color">New server name color</param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetServerNameColor(FColor Color);

	/// <summary>
	/// Sets a new font to the server name and updates the TitleTextBlock font variable.
	/// </summary>
	/// <param name="Font">New server name font</param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetServerTextFont(FSlateFontInfo Font);

	/// <summary>
	/// Sets new users number. Used to change the displayed amount of users and updates the text variable.
	/// </summary>
	/// <param name="Text">New text amount of the users on the server</param>
	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetUsers(int UsersNumber, int MaxUsersNumber);

	/// <summary>
	/// Sets new users text. Used to change the displayed amount of users and updates the UsersTextBlock text variable.
	/// </summary>
	/// <param name="Text">New text amount of the users on the server</param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetUsersText(FText Text);

	/// <summary>
	/// Sets a new color to the users text and updates the UsersTextBlock color variable.
	/// </summary>
	/// <param name="Color">New color</param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetUsersTextColor(FColor Color);

	/// <summary>
	/// Sets a new font to the users amout text and updates the UsersTextBlock font variable.
	/// </summary>
	/// <param name="Font">New Font</param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetUsersTextFont(FSlateFontInfo Font);

	/// <summary>
	/// Sets the current ping and updates the text variable.
	/// </summary>
	/// <param name="Text">New Ping</param>
	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetPing(int PingValue);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetUsersValue(int Value);

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetMaxUsersValue(int Value);

	/// <summary>
	/// Sets the current ping(in FText) and updates the PingTextBlock text variable.
	/// </summary>
	/// <param name="Text"></param>
	UFUNCTION()
	void SetPingText(FText Text);

	/// <summary>
	/// Sets the ping text color and updates the PingTextBlock color variable.
	/// </summary>
	/// <param name="Color"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetPingTextColor(FColor Color);

	/// <summary>
	/// Sets the IP address value.
	/// </summary>
	/// <param name="IPAdress"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetIPAdress(FString IPAdress);

	/// <summary>
	/// Sets the ip address text color.
	/// </summary>
	/// <param name="Color"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetIPTextColor(FColor Color);

	/// <summary>
	/// Sets the IP address text font.
	/// </summary>
	/// <param name="Font"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetIPTextFont(FSlateFontInfo Font);

	/// <summary>
	/// Sets the ping font.
	/// </summary>
	/// <param name="Font"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetPingTextFont(FSlateFontInfo Font);

	/// <summary>
	/// Set to use ping icco material.
	/// </summary>
	/// <param name="Value"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetUsePingIcoMaterial(bool Value);

	/// <summary>
	/// Set Ping Ico material.
	/// </summary>
	/// <param name="Material"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetPingMaterial(UMaterialInterface* Material);

	/// <summary>
	/// Returns Server Info.
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Get")
	FServerInfo GetServerInfo();

	/// <summary>
	/// Show or hide server name.
	/// </summary>
	/// <param name="Show"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetShowServerName(bool Show);

	/// <summary>
	/// Set or hide users.
	/// </summary>
	/// <param name="Show"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetShowUsers(bool Show);

	/// <summary>
	/// Set or hide ping value.
	/// </summary>
	/// <param name="Show"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetShowPing(bool Show);

	/// <summary>
	/// Set or hide ip address.
	/// </summary>
	/// <param name="Show"></param>
	UFUNCTION(BlueprintSetter, Category = "Set")
	void SetShowIp(bool Show);

	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnJoinClickedEvent OnJoinClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnJoinPressedEvent OnJoinPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnJoinReleasedEvent OnJoinReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnJoinHoverEvent OnJoinHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnJoinUnHoverEvent OnJoinUnHovered;

	/// <summary>
	/// True if you want to see the server name.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowServerName, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name"))
	bool bShowServerName;

	/// <summary>
	/// True if you want to see the users amount.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowUsers, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name"))
	bool bShowUsers;

	/// <summary>
	/// True if you want to see the ping value.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowPing, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name"))
	bool bShowPing;

	/// <summary>
	/// True if you want to see the IP address.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowIp, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name"))
	bool bShowIp;

	/// <summary>
	/// Server Name
	/// </summary>
	/*Text settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetServerNameText, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name"))
	FText ServerNameText;

	/// <summary>
	/// Server Name Text Color
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetServerNameColor, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name Color"))
	FColor ServerNameColor;

	/// <summary>
	/// Server Name Text Font
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetServerTextFont, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Server Name Font"))
	FSlateFontInfo ServerTextFont; 

	FText UsersText;

	/// <summary>
	/// User amount text color
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUsersTextColor, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Users Color"))
	FColor UsersColor;

	/// <summary>
	/// User text font
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUsersTextFont, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Users Font"))
	FSlateFontInfo UsersTextFont;

	/// <summary>
	/// IP text color
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetIPTextColor, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "IP Color"))
	FColor IPColor;

	/// <summary>
	/// User text font
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetIPTextFont, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "IP Font"))
	FSlateFontInfo IPTextFont;

	/// <summary>
	/// Current users amount.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUsersValue, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Users On The Server"))
	int Users;

	/// <summary>
	/// Max users amount.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetMaxUsersValue, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Max Users On The Server"))
	int MaxUsers;

	/// <summary>
	/// Current ping amount.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetPing, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Ping"))
	int Ping;

	/// <summary>
	/// Ping text Color
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetPingTextColor, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Ping Color"))
	FColor PingTextColor;

	/// <summary>
	/// Ping text font
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetPingTextFont, Category = "Settings|Style", meta = (AllowPrivateAccess = "true", DisplayName = "Ping Font"))
	FSlateFontInfo PingTextFont;

	/// <summary>
	/// Good ping value.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Good Ping Value"))
	float GoodPingValue;

	/// <summary>
	/// Bad ping value.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Bad Ping Value"))
	float BadPingValue;

	/// <summary>
	/// Show ping icon?
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUsePingIcoMaterial, Category = "Settings|Style", meta = (AllowPrivateAccess = "true"))
	bool bUsePingIcoMaterial;

	/// <summary>
	/// Ping icon material
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetPingMaterial, Category = "Settings|Style", meta = (DisplayName = "Ping Material", EditCondition = "bUsePingIcoMaterial == true", EditConditionHides))
	UMaterialInterface* PingMaterial;

	/// <summary>
	/// Ping Icon Material instance
	/// </summary>
	UMaterialInstanceDynamic* PingMaterialInstance;

	/// <summary>
	/// IP string. Used to store IP address.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetIPAdress, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "IP"))
	FString IP;

	/// <summary>
	/// String variable. Used to store additional data.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Additional Data"))
	FString AdditionalData;

private:

	UFUNCTION()
	void Join_Clicked();

	UFUNCTION()
	void Join_Pressed();

	UFUNCTION()
	void Join_Released();

	UFUNCTION()
	void Join_Hovered();

	UFUNCTION()
	void Join_UnHovered();

};
