//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/TextChatWidget.h"
#include "TextChatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVANCEDMENUSYSTEM_API UTextChatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTextChatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Open text chat widget.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Chat")
	void OpenChat();

	/// <summary>
	/// Close text chat widget.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Chat")
	void CloseChat();

	/// <summary>
	/// Add user message to chat.
	/// </summary>
	/// <param name="User">User name</param>
	/// <param name="Message">Message</param>
	/// <param name="Color">Message color</param>
	/// <param name="Font">Message font</param>
	/// <param name="CustomStyle">Use custom style for this message</param>
	void AddChatUserMessage(FString User, FString Message, FColor Color, FSlateFontInfo Font, bool CustomStyle = false);

	/// <summary>
	/// Add user message to chat. Send the message to the server.
	/// </summary>
	/// <param name="User">User name</param>
	/// <param name="Message">Message</param>
	/// <param name="Color">Message color</param>
	/// <param name="Font">Message font</param>
	/// <param name="CustomStyle">Use custom style for this message</param>
	/// <warning>Already in use for the network replication.</warning>
	UFUNCTION(Reliable, Server, WithValidation)
	void AddChatUserMessage_Server(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, bool CustomStyle = false);

	/// <summary>
	/// Add user message to chat. Send the message to the server validation.
	/// </summary>
	/// <param name="User">User name</param>
	/// <param name="Message">Message</param>
	/// <param name="Color">Message color</param>
	/// <param name="Font">Message font</param>
	/// <param name="CustomStyle">Use custom style for this message</param>
	/// <warning>Already in use for the network replication.</warning>
	bool AddChatUserMessage_Server_Validate(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, bool CustomStyle = false);

	void AddChatUserMessage_Server_Implementation(const FString& User, const FString& Messageconst, FColor Color, const FSlateFontInfo Font, bool CustomStyle = false);

	/// <summary>
	/// Add user message to chat. Send message to the clients.
	/// </summary>
	/// <param name="User">User name</param>
	/// <param name="Message">Message</param>
	/// <param name="Color">Message color</param>
	/// <param name="Font">Message font</param>
	/// <param name="CustomStyle">Use custom style for this message</param>
	/// <warning>Already in use for the network replication.</warning>
	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void AddChatUserMessage_Multicast(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, const bool CustomStyle = false);

	/// <summary>
	/// Add user message to chat. Send message to the clients validation.
	/// </summary>
	/// <param name="User">User name</param>
	/// <param name="Message">Message</param>
	/// <param name="Color">Message color</param>
	/// <param name="Font">Message font</param>
	/// <param name="CustomStyle">Use custom style for this message</param>
	/// <warning>Already in use for the network replication.</warning>
	bool AddChatUserMessage_Multicast_Validate(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, const bool CustomStyle = false);

	void AddChatUserMessage_Multicast_Implementation(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, const bool CustomStyle = false);

	/// <summary>
	/// Chat Widget Class.
	/// </summary>
	/// <note>Must be child of UTextChatWidget</note>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true", DisplayName = "Chat Widget Class"))
	TSubclassOf<class UUserWidget> WidgetClass;

	UTextChatWidget* Widget;

};
