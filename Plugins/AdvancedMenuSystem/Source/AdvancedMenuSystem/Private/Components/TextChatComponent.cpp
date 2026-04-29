//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

#include "Components/TextChatComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTextChatComponent::UTextChatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTextChatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->GetClass()->IsChildOf(APawn::StaticClass()) || GetOwner()->GetClass()->IsChildOf(APlayerController::StaticClass()))
	{
		AController* Controller;

		if (GetOwner()->GetClass()->IsChildOf(APawn::StaticClass()))
		{
			Controller = Cast<APawn>(GetOwner())->GetController();
		}
		else
		{
			Controller = Cast<APlayerController>(GetOwner());
		}

		if (Controller)
		{
			if (Controller->IsLocalController())
			{
				Widget = CreateWidget<UTextChatWidget>(UGameplayStatics::GetGameInstance(GetWorld()), WidgetClass);

				if (Widget) 
				{
					Widget->AddToViewport();
					Widget->ExitChat();

					Widget->bLocalPlayer = true;
				}
			}
		}

	}
	
}


// Called every frame
void UTextChatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTextChatComponent::OpenChat()
{
	if (Widget)
	{
		Widget->FocusChat();
	}
}

void UTextChatComponent::CloseChat()
{
	if (Widget)
	{
		Widget->ExitChat();
	}
}

void UTextChatComponent::AddChatUserMessage(FString User, FString Message, FColor Color, FSlateFontInfo Font, bool CustomStyle)
{
	if (GetOwner()->HasAuthority())
	{
		AddChatUserMessage_Multicast(User, Message, Color, Font, false);
	}
	else
	{
		AddChatUserMessage_Server(User, Message, Color, Font, false);
	}
}

bool UTextChatComponent::AddChatUserMessage_Server_Validate(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, bool CustomStyle)
{
	return true;
}

void UTextChatComponent::AddChatUserMessage_Server_Implementation(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, bool CustomStyle)
{
	AddChatUserMessage_Multicast(User, Message, Color, Font, false);
}

bool UTextChatComponent::AddChatUserMessage_Multicast_Validate(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, bool CustomStyle)
{
	return true;
}

void UTextChatComponent::AddChatUserMessage_Multicast_Implementation(const FString& User, const FString& Message, const FColor Color, const FSlateFontInfo Font, bool CustomStyle)
{
	if (Widget)
	{
		Widget->AddChatUserMessage(User, Message, Color, Font, false);
	}
}