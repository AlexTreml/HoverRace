//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Widgets/MovableWindowWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Widgets/ServerSlotWidget.h"
#include "ServerBrowserWindowWidget.generated.h"

/// <summary>
/// Server browser movable window widget.
/// </summary>
UCLASS()
class ADVANCEDMENUSYSTEM_API UServerBrowserWindowWidget : public UMovableWindowWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseClickedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClosePressedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseReleasedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseHoverEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseUnHoverEvent);

public:

	UServerBrowserWindowWidget(const FObjectInitializer& ObjectInitializer);

	//Same as Begin Play
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/// <summary>
	/// Adds example servers
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Add")
	void AddExampleServers();

	/// <summary>
	/// Add Server to the scroll box. 
	/// </summary>
	/// <param name="ServerName">Name of the server</param>
	/// <param name="UsersNumber">Current amount of the users</param>
	/// <param name="MaxUsersNumber">Max Amount of the users</param>
	/// <param name="Ping">Current ping value</param>
	/// <param name="IPAdress">Server IP address</param>
	/// <param name="OtherData">Other data to store</param>
	UFUNCTION(BlueprintCallable, Category = "Add")
	void AddServer(FText ServerName, int UsersNumber, int MaxUsersNumber, int Ping, FString IPAdress, FString OtherData);

	/// <summary>
	/// Updates the server by name.
	/// </summary>
	/// <param name="ServerName">Name of the server</param>
	/// <param name="UsersNumber">Current amount of the users</param>
	/// <param name="MaxUsersNumber">Max Amount of the users</param>
	/// <param name="Ping">Current ping value</param>
	/// <param name="IPAdress">Server IP address</param>
	/// <param name="OtherData">Other data to store</param>
	/// <param name="NewServerName">New server name</param>
	/// <param name="UpdateName">Update name</param>
	UFUNCTION(BlueprintCallable, Category = "Update")
	void UpdateServerByName(FString ServerName, int UsersNumber, int MaxUsersNumber, int Ping, FString IPAdress, FString OtherData, FText NewServerName, bool UpdateName = false);

	/// <summary>
	/// Remove sever by name.
	/// </summary>
	/// <param name="ServerName">Name of the server</param>
	UFUNCTION(BlueprintCallable, Category = "Update")
	void RemoveServerByName(FString ServerName);

	/// <summary>
	/// Remove server by index from servers widgets.
	/// </summary>
	/// <param name="Index"></param>
	UFUNCTION(BlueprintCallable, Category = "Update")
	void RemoveServerByIndex(int Index);

	/// <summary>
	/// Searches server index by name.
	/// </summary>
	/// <param name="ServerName">Name of the server</param>
	/// <param name="Index"></param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Get")
	bool GetServerIndexByName(FString ServerName, int& Index);

	/// <summary>
	/// Close window button.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	class UButton* CloseButton;

	/// <summary>
	/// Scroll box to which servers are added.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* ScrollBox;

	/// <summary>
	/// Server slot class.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UServerSlotWidget> ServerSlotClass;

	/// <summary>
	/// Set to true if you want to add test servers.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bAddExampleServersOnStart;

	/// <summary>
	/// Server slot widgets.
	/// </summary>
	TArray<UServerSlotWidget*> ServersWidgets;

	UFUNCTION(BlueprintCallable, Category = "Get")
	FORCEINLINE TArray<UServerSlotWidget*> GetServerSlotWidgetsArray() const { return ServersWidgets; };

	UFUNCTION(BlueprintSetter)
	void SetShowServerName(bool Show);

	UFUNCTION(BlueprintSetter)
	void SetShowUsers(bool Show);

	UFUNCTION(BlueprintSetter)
	void SetShowPing(bool Show);

	UFUNCTION(BlueprintSetter)
	void SetShowIp(bool Show);

	UFUNCTION(BlueprintSetter)
	void SetUsePingIco(bool Value);

	/// <summary>
	/// Set to true if you want to show server name.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowServerName, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Show Server Name"))
	bool bShowServerName;

	/// <summary>
	/// Set to true to show users.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowUsers, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Show Users"))
	bool bShowUsers;

	/// <summary>
	/// Set to true if you want to show ping.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowPing, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Show Ping"))
	bool bShowPing;

	/// <summary>
	/// Set to true if you want to show IP.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetShowIp, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Show Ip"))
	bool bShowIp;

	/// <summary>
	/// Set to true if you want to show ping icon.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUsePingIco, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Use Ping Ico"))
	bool bUsePingIco;

	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnCloseClickedEvent OnCloseClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnClosePressedEvent OnClosePressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnCloseReleasedEvent OnCloseReleased;

	/** Called when the button is hovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnCloseHoverEvent OnCloseHovered;

	/** Called when the button is unhovered */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnCloseUnHoverEvent OnCloseUnHovered;

private:

	/// <summary>
	/// This function executes when "close" button is clicked.
	/// </summary>
	UFUNCTION()
	void Close_Clicked();

	/// <summary>
	/// This function executes when "close" button is pressed.
	/// </summary>
	UFUNCTION()
	void Close_Pressed();

	/// <summary>
	/// This function executes when "close" button is released.
	/// </summary>
	UFUNCTION()
	void Close_Released();

	/// <summary>
	/// This function executes when "close" button is hovered.
	/// </summary>
	UFUNCTION()
	void Close_Hovered();

	/// <summary>
	/// This function executes when "close" button is unhovered.
	/// </summary>
	UFUNCTION()
	void Close_UnHovered();

};
