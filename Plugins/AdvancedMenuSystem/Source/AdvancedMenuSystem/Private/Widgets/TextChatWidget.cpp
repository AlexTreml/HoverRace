//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/TextChatWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/Font.h"
#include "Kismet/KismetMathLibrary.h"
#include "Save/MultiplayerSave.h"
#include "Components/TextChatComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

UTextChatWidget::UTextChatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> TileMat(TEXT("Material'/AdvancedMenuSystem/Demo/Materials/M_Tile.M_Tile'"));

		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		UserMessagePreviewTextFont = DefaultFont;
		GlobalMessagePreviewTextFont = DefaultFont;
	}

	UserMessagePreviewText = FText::AsCultureInvariant("User: Message");
	UserMessagePreviewTextColor = FColor(255, 255, 255);

	GlobalMessagePreviewText = FText::AsCultureInvariant("Global Message");
	GlobalMessagePreviewTextColor = FColor(255, 255, 255);

	bChatFocused = false;
	ScrollMultiplier = 1.f;
}

void UTextChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UserMessageTextPreview->SetVisibility(ESlateVisibility::Collapsed);
	GlobalMessageTextPreview->SetVisibility(ESlateVisibility::Collapsed);

	if (!EditField->OnTextCommitted.IsAlreadyBound(this, &UTextChatWidget::OnTextCommited))
	{
		EditField->OnTextCommitted.AddDynamic(this, &UTextChatWidget::OnTextCommited);
	}
}

void UTextChatWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UpdatePreviewText();

}

void UTextChatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();  

	//if (auto RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootWidget")))
	//{
	//	//EditField = WidgetTree->ConstructWidget<UEditableText>(UEditableText::StaticClass(), TEXT("UEditableText"));
	//	/*if (EditField)
	//	{
	//		if (const auto RootWidgetSlot = RootWidget->AddChildToCanvas(EditField))
	//		{
	//			RootWidgetSlot->SetAutoSize(true);
	//			RootWidgetSlot->SetAnchors(FAnchors(0,0,1,1)); RootWidgetSlot->SetOffsets(FMargin(0,0));
	//		}
	//		WidgetTree->RootWidget = RootWidget;
	//	}*/
	//}
}

void UTextChatWidget::UpdatePreviewText()
{
	if (UserMessageTextPreview)
	{
		UserMessageTextPreview->SetText(UserMessagePreviewText);
		UserMessageTextPreview->SetColorAndOpacity(UserMessagePreviewTextColor);
		UserMessageTextPreview->SetFont(UserMessagePreviewTextFont);
	}

	if (GlobalMessageTextPreview)
	{
		GlobalMessageTextPreview->SetText(GlobalMessagePreviewText);
		GlobalMessageTextPreview->SetColorAndOpacity(GlobalMessagePreviewTextColor);
		GlobalMessageTextPreview->SetFont(GlobalMessagePreviewTextFont);
	}
}

void UTextChatWidget::AddChatUserMessage(FString User, FString Message,FColor Color, FSlateFontInfo Font, bool CustomStyle)
{
	UTextBlockWidget* TextBlockWidget = WidgetTree->ConstructWidget<UTextBlockWidget>(UTextBlockWidget::StaticClass(), *(FString("TextBlockWidget") + FString::FromInt(MessagesTextBlockArr.Num())));
	
	if (TextBlockWidget)
	{
		//Set Message text
		TextBlockWidget->SetText(FText::AsCultureInvariant(User + ": " + Message));
		
		//Set Font
		if (CustomStyle)
		{
			TextBlockWidget->SetTextFont(Font);
			TextBlockWidget->SetTextColor(Color);
		}
		else
		{
			TextBlockWidget->SetTextFont(UserMessagePreviewTextFont);
			TextBlockWidget->SetTextColor(UserMessagePreviewTextColor);
		}

		MessagesTextBlockArr.Add(TextBlockWidget);

		if (const auto RootWidgetSlot = ScrollBox->AddChild(TextBlockWidget))
		{
			
		}

	}
}

void UTextChatWidget::AddChatGlobalMessage(FString Message, FColor Color, FSlateFontInfo Font, bool CustomStyle)
{
	UTextBlockWidget* TextBlockWidget = WidgetTree->ConstructWidget<UTextBlockWidget>(UTextBlockWidget::StaticClass(), *(FString("TextBlockWidget") + FString::FromInt(MessagesTextBlockArr.Num())));

	if (TextBlockWidget)
	{
		//Set Message text
		TextBlockWidget->SetText(FText::AsCultureInvariant(Message));
		
		//Set Font
		if (CustomStyle)
		{
			TextBlockWidget->SetTextFont(Font);
			TextBlockWidget->SetTextColor(Color);
		}
		else
		{
			TextBlockWidget->SetTextFont(GlobalMessagePreviewTextFont);
			TextBlockWidget->SetTextColor(GlobalMessagePreviewTextColor);
		}

		MessagesTextBlockArr.Add(TextBlockWidget);

		if (const auto RootWidgetSlot = ScrollBox->AddChild(TextBlockWidget))
		{
			
		}

	}
}

void UTextChatWidget::SetUpChatComponent()
{
	APlayerController* PlayerController;

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController->GetComponentByClass(UTextChatComponent::StaticClass()))
	{
		ParentComponent = Cast<UTextChatComponent>(PlayerController->GetComponentByClass(UTextChatComponent::StaticClass()));
	}
}

void UTextChatWidget::FocusChat()
{
	APlayerController* PlayerController; 

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	EditField->SetUserFocus(PlayerController);

	EditField->SetIsEnabled(true);

	bChatFocused = true;

}

void UTextChatWidget::ExitChat()
{
	bChatFocused = false;

	EditField->SetText(FText::AsCultureInvariant(""));

	EditField->SetIsEnabled(false);
}

void UTextChatWidget::Scroll(bool Up)
{
	float Speed;

	if (Up)
	{
		Speed = 1.f;
	}
	else
	{
		Speed = -1.f;
	}

	Speed *= ScrollMultiplier;

	float ScroolOffset = Speed + ScrollBox->GetScrollOffset();

	ScroolOffset = UKismetMathLibrary::FClamp(ScroolOffset, 0, ScrollBox->GetScrollOffsetOfEnd());

	ScrollBox->SetScrollOffset(ScroolOffset);

}

void UTextChatWidget::SetUserMessageTextPreview(FText Text)
{
	UserMessagePreviewText = Text;
}

void UTextChatWidget::SetUserMessageTextPreviewColor(FColor Color)
{
	UserMessagePreviewTextColor = Color;
}

void UTextChatWidget::SetUserMessageTextPreviewFont(FSlateFontInfo Font)
{
	UserMessagePreviewTextFont = Font;
}


void UTextChatWidget::SetGlobalMessageTextPreview(FText Text)
{
	GlobalMessagePreviewText = Text;
}

void UTextChatWidget::SetGlobalMessageTextPreviewColor(FColor Color)
{
	GlobalMessagePreviewTextColor = Color;
}

void UTextChatWidget::SetGlobalMessageTextPreviewFont(FSlateFontInfo Font)
{
	GlobalMessagePreviewTextFont = Font;
}

void UTextChatWidget::OnTextCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (ETextCommit::OnEnter)
	{
		FString UserName = "User";

		UMultiplayerSave* MultiplayerSave = Cast<UMultiplayerSave>(UGameplayStatics::CreateSaveGameObject(UMultiplayerSave::StaticClass()));

		if (MultiplayerSave)
		{
			if (UGameplayStatics::DoesSaveGameExist(MultiplayerSave->SaveSlotName, MultiplayerSave->DefaultUserIndex))
			{
				MultiplayerSave = Cast<UMultiplayerSave>(UGameplayStatics::LoadGameFromSlot(MultiplayerSave->SaveSlotName, MultiplayerSave->DefaultUserIndex));
			}

			if (MultiplayerSave)
			{
				UserName = MultiplayerSave->Nickname;
			}
		}

		if (!Text.ToString().IsEmpty())
		{
			if (ParentComponent)
			{
				UTextChatComponent* TextChatComponent;

				TextChatComponent = Cast<UTextChatComponent>(ParentComponent);

				if (TextChatComponent)
				{
					TextChatComponent->AddChatUserMessage(UserName, Text.ToString(), UserMessagePreviewTextColor, UserMessagePreviewTextFont, false);
				}

				ExitChat();
			}
			else 
			{
				AddChatUserMessage(UserName, Text.ToString(), UserMessagePreviewTextColor, UserMessagePreviewTextFont, false);

				EditField->SetText(FText::AsCultureInvariant(""));
			}
		}
	}
}
