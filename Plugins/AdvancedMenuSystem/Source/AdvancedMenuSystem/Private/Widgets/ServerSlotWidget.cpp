//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/ServerSlotWidget.h"
#include "Engine/Font.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

UServerSlotWidget::UServerSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		SetServerTextFont(DefaultFont);
		SetUsersTextFont(DefaultFont);
		SetPingTextFont(DefaultFont);
		SetIPTextFont(DefaultFont);
	}

	SetServerNameText(FText::AsCultureInvariant("Server Name"));
	SetServerNameColor(FColor::White);

	SetUsers(0, 10);
	SetUsersTextColor(FColor::White);

	SetPing(99);
	SetPingTextColor(FColor::White);

	SetIPAdress("127.0.0.1");
	SetIPTextColor(FColor::White);

	GoodPingValue = 10.f;
	BadPingValue = 100.f;

	bShowServerName = true;
	bShowUsers = true;
	bShowPing = true;
	bShowIp = true;
	bUsePingIcoMaterial = true;
}

void UServerSlotWidget::SynchronizeProperties() 
{
	Super::SynchronizeProperties();

	//Server Name
	SetServerNameText(ServerNameText);
	SetServerNameColor(ServerNameColor);
	SetServerTextFont(ServerTextFont);

	if (bShowServerName)
	{
		TitleTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TitleTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	//Users
	SetUsers(Users,MaxUsers);
	SetUsersTextColor(UsersColor);
	SetUsersTextFont(UsersTextFont);

	if (bShowUsers)
	{
		UsersTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UsersTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	//Ping
	SetPing(Ping);
	SetPingTextColor(PingTextColor);
	SetPingTextFont(PingTextFont);

	if (bShowPing)
	{
		PingTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PingTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	//IP
	SetIPAdress(IP);
	SetIPTextColor(IPColor);
	SetIPTextFont(IPTextFont); 

	if (bShowIp)
	{
		IPAdressTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		IPAdressTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (bUsePingIcoMaterial)
	{
		PingIco->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PingIco->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (PingIco)
	{
		if (!PingMaterialInstance && PingMaterial)
		{
			PingMaterialInstance = UMaterialInstanceDynamic::Create(PingMaterial, this);

			FSlateBrush Brush;
			Brush.SetResourceObject(PingMaterialInstance);

			PingIco->SetBrush(Brush);
		}
	}
}

//Same as Begin Play
void UServerSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Server Name
	SetServerNameText(ServerNameText);
	SetServerNameColor(ServerNameColor);
	SetServerTextFont(ServerTextFont);

	if (bShowServerName)
	{
		TitleTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TitleTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	//Users
	SetUsers(Users, MaxUsers);
	SetUsersTextColor(UsersColor);
	SetUsersTextFont(UsersTextFont);

	if (bShowUsers)
	{
		UsersTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UsersTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	//Ping
	SetPing(Ping);
	SetPingTextColor(PingTextColor);
	SetPingTextFont(PingTextFont);

	if (bShowPing)
	{
		PingTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PingTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	//IP
	SetIPAdress(IP);
	SetIPTextColor(IPColor);
	SetIPTextFont(IPTextFont);

	if (bUsePingIcoMaterial)
	{
		PingIco->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PingIco->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (PingIco)
	{
		if (!PingMaterialInstance && PingMaterial)
		{
			PingMaterialInstance = UMaterialInstanceDynamic::Create(PingMaterial, this);

			FSlateBrush Brush;
			Brush.SetResourceObject(PingMaterialInstance);

			PingIco->SetBrush(Brush);
		}
	}

	if (JoinButton)
	{
		JoinButton->OnPressed.Clear();
		JoinButton->OnPressed.Clear();
		JoinButton->OnReleased.Clear();
		JoinButton->OnHovered.Clear();
		JoinButton->OnUnhovered.Clear();

		JoinButton->OnPressed.AddDynamic(this, &UServerSlotWidget::Join_Clicked);
		JoinButton->OnPressed.AddDynamic(this, &UServerSlotWidget::Join_Pressed);
		JoinButton->OnReleased.AddDynamic(this, &UServerSlotWidget::Join_Released);
		JoinButton->OnHovered.AddDynamic(this, &UServerSlotWidget::Join_Hovered);
		JoinButton->OnUnhovered.AddDynamic(this, &UServerSlotWidget::Join_UnHovered);
	}
}

void UServerSlotWidget::UpdateServerData(FText ServerName, int UsersNumber, int MaxUsersNumber, int PingValue, FString IPAdress, FString OtherData)
{
	SetServerNameText(ServerName);

	SetUsers(UsersNumber, MaxUsersNumber);

	SetPing(PingValue);

	IP = IPAdress;

	AdditionalData = OtherData;
}

void UServerSlotWidget::SetServerNameText(FText Text)
{
	ServerNameText = Text;

	if (TitleTextBlock)
	{
		TitleTextBlock->SetText(Text);
	}
}

void UServerSlotWidget::SetServerNameColor(FColor Color)
{
	ServerNameColor = Color;

	if (TitleTextBlock)
	{
		TitleTextBlock->SetColorAndOpacity(Color);
	}
}

void UServerSlotWidget::SetServerTextFont(FSlateFontInfo Font)
{
	ServerTextFont = Font;

	if (TitleTextBlock)
	{
		TitleTextBlock->SetFont(Font);
	}
}

void UServerSlotWidget::SetUsers(int UsersNumber, int MaxUsersNumber)
{
	Users = UsersNumber;

	MaxUsers = MaxUsersNumber;

	FString SUsers = FString::FromInt(UsersNumber) + "/" + FString::FromInt(MaxUsersNumber);

	SetUsersText(FText::AsCultureInvariant(SUsers));
}

void UServerSlotWidget::SetUsersText(FText Text)
{
	UsersText = Text;

	if (UsersTextBlock)
	{
		UsersTextBlock->SetText(Text);
	}
}

void UServerSlotWidget::SetUsersTextColor(FColor Color)
{
	UsersColor = Color;

	if (UsersTextBlock)
	{
		UsersTextBlock->SetColorAndOpacity(Color);
	}
}

void UServerSlotWidget::SetUsersTextFont(FSlateFontInfo Font)
{
	UsersTextFont = Font;

	if (UsersTextBlock)
	{
		UsersTextBlock->SetFont(Font);
	}
}

void UServerSlotWidget::SetPing(int PingValue)
{
	Ping = PingValue;
	FString Str = FString::FromInt(Ping) + "ms";

	SetPingText(FText::AsCultureInvariant(Str));

	if (PingIco)
	{
		PingIco->GetDynamicMaterial();

		if (bUsePingIcoMaterial && PingMaterialInstance)
		{
			float Quality = UKismetMathLibrary::MapRangeClamped(Ping, GoodPingValue, BadPingValue, 1.f, 0.f);
			PingMaterialInstance->SetScalarParameterValue("PingQuality", Quality);
		}
	}
}

void UServerSlotWidget::SetPingText(FText Text)
{
	if (PingTextBlock)
	{
		PingTextBlock->SetText(Text);
	}
}

void UServerSlotWidget::SetPingTextColor(FColor Color)
{
	PingTextColor = Color;

	if (PingTextBlock)
	{
		PingTextBlock->SetColorAndOpacity(Color);
	}
}

void UServerSlotWidget::SetPingTextFont(FSlateFontInfo Font)
{
	PingTextFont = Font;

	if (PingTextBlock)
	{
		PingTextBlock->SetFont(Font);
	}
}

void UServerSlotWidget::SetUsePingIcoMaterial(bool Value)
{
	bUsePingIcoMaterial = Value;

	if (bUsePingIcoMaterial)
	{
		PingIco->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PingIco->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UServerSlotWidget::SetPingMaterial(UMaterialInterface* Material)
{
	PingMaterial = Material;

	PingMaterialInstance = UMaterialInstanceDynamic::Create(PingMaterial, this);

	FSlateBrush Brush;
	Brush.SetResourceObject(PingMaterialInstance);

	PingIco->SetBrush(Brush);
}

FServerInfo UServerSlotWidget::GetServerInfo()
{
	FServerInfo ServerInfo;

	ServerInfo.ServerName = ServerNameText;
	ServerInfo.UsersNumber = Users;
	ServerInfo.MaxUsersNumber = MaxUsers;
	ServerInfo.Ping = Ping;
	ServerInfo.IPAdress = IP;
	ServerInfo.OtherData = AdditionalData;

	return ServerInfo;
};

void UServerSlotWidget::SetIPAdress(FString IPAdress)
{
	IP = IPAdress;

	if (IPAdressTextBlock)
	{
		IPAdressTextBlock->SetText(FText::AsCultureInvariant(IP));
	}
}

void UServerSlotWidget::SetUsersValue(int Value)
{
	Users = Value;

	SetUsers(Users, MaxUsers);
}

void UServerSlotWidget::SetMaxUsersValue(int Value)
{
	MaxUsers = Value;

	SetUsers(Users, MaxUsers);
}

void UServerSlotWidget::SetIPTextColor(FColor Color)
{
	IPColor = Color;

	if (IPAdressTextBlock)
	{
		IPAdressTextBlock->SetColorAndOpacity(Color);
	}
}

void UServerSlotWidget::SetIPTextFont(FSlateFontInfo Font)
{
	IPTextFont = Font;

	if (IPAdressTextBlock)
	{
		IPAdressTextBlock->SetFont(Font);
	}
}

void UServerSlotWidget::SetShowServerName(bool Show)
{
	bShowServerName = Show;

	if (bShowServerName)
	{
		TitleTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TitleTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UServerSlotWidget::SetShowUsers(bool Show)
{
	bShowUsers = Show;

	if (bShowUsers)
	{
		UsersTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UsersTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UServerSlotWidget::SetShowPing(bool Show)
{
	bShowPing = Show;

	if (bShowPing)
	{
		PingTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PingTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UServerSlotWidget::SetShowIp(bool Show)
{
	bShowIp = Show;

	if (bShowIp)
	{
		IPAdressTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		IPAdressTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UServerSlotWidget::Join_Clicked()
{
	OnJoinClicked.Broadcast();
}

void UServerSlotWidget::Join_Pressed()
{
	OnJoinPressed.Broadcast();
}

void UServerSlotWidget::Join_Released()
{
	OnJoinReleased.Broadcast();
}

void UServerSlotWidget::Join_Hovered()
{
	OnJoinHovered.Broadcast();
}

void UServerSlotWidget::Join_UnHovered()
{
	OnJoinUnHovered.Broadcast();
}