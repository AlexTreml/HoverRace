//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/ServerBrowserWindowWidget.h"
#include "Blueprint/WidgetTree.h"

UServerBrowserWindowWidget::UServerBrowserWindowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WindowTitleText = FText::AsCultureInvariant("Server Browser");

	bShowServerName = true;
	bShowUsers = true;
	bShowPing = true;
	bShowIp = true;
	bUsePingIco = true;
}

void UServerBrowserWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bAddExampleServersOnStart)
	{
		AddExampleServers();
	}

	if (CloseButton)
	{
		CloseButton->OnPressed.Clear();
		CloseButton->OnPressed.Clear();
		CloseButton->OnReleased.Clear();
		CloseButton->OnHovered.Clear();
		CloseButton->OnUnhovered.Clear();

		CloseButton->OnPressed.AddDynamic(this, &UServerBrowserWindowWidget::Close_Clicked);
		CloseButton->OnPressed.AddDynamic(this, &UServerBrowserWindowWidget::Close_Pressed);
		CloseButton->OnReleased.AddDynamic(this, &UServerBrowserWindowWidget::Close_Released);
		CloseButton->OnHovered.AddDynamic(this, &UServerBrowserWindowWidget::Close_Hovered);
		CloseButton->OnUnhovered.AddDynamic(this, &UServerBrowserWindowWidget::Close_UnHovered);
	}
}

void UServerBrowserWindowWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UServerBrowserWindowWidget::AddServer(FText ServerName, int UsersNumber, int MaxUsersNumber, int Ping, FString IPAdress, FString OtherData)
{
	if (ServerSlotClass && ScrollBox)
	{
		UServerSlotWidget* ServerSlot = WidgetTree->ConstructWidget<UServerSlotWidget>(ServerSlotClass, *(FString("ServerSlot") + FString::FromInt(ServersWidgets.Num())));

		if (ServerSlot)
		{
			/*Setting Title Text*/
			ServerSlot->UpdateServerData(ServerName, UsersNumber, MaxUsersNumber, Ping, IPAdress, OtherData);

			ServerSlot->SetShowServerName(bShowServerName);
			ServerSlot->SetShowUsers(bShowUsers);
			ServerSlot->SetShowPing(bShowPing);
			ServerSlot->SetShowIp(bShowIp);
			ServerSlot->SetUsePingIcoMaterial(bUsePingIco);

			ServersWidgets.Add(ServerSlot);

			if (const auto RootWidgetSlot = ScrollBox->AddChild(ServerSlot))
			{
				
			}
		}
	}
}

void UServerBrowserWindowWidget::UpdateServerByName(FString ServerName, int UsersNumber, int MaxUsersNumber, int Ping, FString IPAdress, FString OtherData, FText NewServerName, bool UpdateName)
{
	if (ServersWidgets.Num())
	{
		int Index = 0;
		bool bFound = false;

		bFound = GetServerIndexByName(ServerName, Index);

		if (bFound && ServersWidgets.IsValidIndex(Index))
		{
			FString Name;

			if (UpdateName)
			{
				Name = NewServerName.ToString();
			}
			else
			{
				Name = ServerName;
			}

			ServersWidgets[Index]->UpdateServerData(FText::AsCultureInvariant(ServerName), UsersNumber, MaxUsersNumber, Ping, IPAdress, OtherData);
		}
	}
}

void UServerBrowserWindowWidget::RemoveServerByName(FString ServerName)
{
	if (ServersWidgets.Num())
	{
		int Index = 0;
		bool bFound = false;

		bFound = GetServerIndexByName(ServerName, Index);

		if (bFound && ServersWidgets.IsValidIndex(Index))
		{
			ServersWidgets[Index]->BeginDestroy();

			ServersWidgets.RemoveAt(Index);
		}
	}
}

void UServerBrowserWindowWidget::RemoveServerByIndex(int Index)
{
	if (ServersWidgets.IsValidIndex(Index))
	{
		ServersWidgets[Index]->BeginDestroy();

		ServersWidgets.RemoveAt(Index);
	}
}

bool UServerBrowserWindowWidget::GetServerIndexByName(FString ServerName, int& Index)
{
	if (!ServersWidgets.IsEmpty())
	{
		bool bFound = false;

		for (int i = 0; i < ServersWidgets.Num(); i++)
		{
			if (ServersWidgets[i]->ServerNameText.ToString() == ServerName)
			{
				Index = i;
				bFound = true;

				break;
			}
		}

		if (bFound && ServersWidgets.IsValidIndex(Index))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void UServerBrowserWindowWidget::AddExampleServers()
{
	TArray<FServerInfo> ExampleServersInfo;

	for (int i = 0; i < 40; i++)
	{
		FServerInfo ServerInfo;

		ServerInfo.ServerName = FText::AsCultureInvariant("ServerNameText " + FString::FromInt(i));
		ServerInfo.UsersNumber = 2*(i+1);
		ServerInfo.MaxUsersNumber = 5*(i+1);

		if (i < 3)
		{
			ServerInfo.Ping = 10 + (30 * i);
		}
		else
		{
			ServerInfo.Ping = 10;
		}

		ServerInfo.IPAdress = "127.0.0.1";
		ServerInfo.OtherData = "{AdditionalData}";

		ExampleServersInfo.Add(ServerInfo);
	}

	for (int i = 0; i < ExampleServersInfo.Num(); i++)
	{
		if (ExampleServersInfo.IsValidIndex(i))
		{
			AddServer(ExampleServersInfo[i].ServerName, ExampleServersInfo[i].UsersNumber, ExampleServersInfo[i].MaxUsersNumber, ExampleServersInfo[i].Ping, ExampleServersInfo[i].IPAdress, ExampleServersInfo[i].OtherData);
		}
	}
}

void UServerBrowserWindowWidget::SetShowServerName(bool Show)
{
	bShowServerName = Show;

	for (int i = 0; i < ServersWidgets.Num(); i++)
	{
		if (ServersWidgets.IsValidIndex(i))
		{
			ServersWidgets[i]->SetShowServerName(bShowServerName);
		}
	}
}

void UServerBrowserWindowWidget::SetShowUsers(bool Show)
{
	bShowUsers = Show;

	for (int i = 0; i < ServersWidgets.Num(); i++)
	{
		if (ServersWidgets.IsValidIndex(i))
		{
			ServersWidgets[i]->SetShowServerName(bShowUsers);
		}
	}
}

void UServerBrowserWindowWidget::SetShowPing(bool Show)
{
	bShowPing = Show;

	for (int i = 0; i < ServersWidgets.Num(); i++)
	{
		if (ServersWidgets.IsValidIndex(i))
		{
			ServersWidgets[i]->SetShowServerName(bShowPing);
		}
	}
}

void UServerBrowserWindowWidget::SetShowIp(bool Show)
{
	bShowIp = Show;

	for (int i = 0; i < ServersWidgets.Num(); i++)
	{
		if (ServersWidgets.IsValidIndex(i))
		{
			ServersWidgets[i]->SetShowServerName(bShowIp);
		}
	}
}

void UServerBrowserWindowWidget::SetUsePingIco(bool Value)
{
	bUsePingIco = Value;

	for (int i = 0; i < ServersWidgets.Num(); i++)
	{
		if (ServersWidgets.IsValidIndex(i))
		{
			ServersWidgets[i]->SetUsePingIcoMaterial(bUsePingIco);
		}
	}
}

void UServerBrowserWindowWidget::Close_Clicked()
{
	OnCloseClicked.Broadcast();
}

void UServerBrowserWindowWidget::Close_Pressed()
{
	OnClosePressed.Broadcast();
}

void UServerBrowserWindowWidget::Close_Released()
{
	OnCloseReleased.Broadcast();
}

void UServerBrowserWindowWidget::Close_Hovered()
{
	OnCloseHovered.Broadcast();
}

void UServerBrowserWindowWidget::Close_UnHovered()
{
	OnCloseUnHovered.Broadcast();
}