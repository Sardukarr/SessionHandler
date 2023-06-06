// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionHandlerMenu.h"
#include "Components/Button.h"
#include "SessionHandlerSubsystem.h"

void USessionHandlerMenu::MenuSetup(int32 NumberOfPublicConnecions, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnecions;
	MatchType = TypeOfMatch;

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		SessionHandlerSubsystem = GameInstance->GetSubsystem<USessionHandlerSubsystem>();
	}
	if (SessionHandlerSubsystem)
	{
		SessionHandlerSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

bool USessionHandlerMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	return true;
}

void USessionHandlerMenu::NativeDestruct()
{
	{
		MenuTearDown();

		Super::NativeDestruct();
	}
}

void USessionHandlerMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("SessionCreateSuccessfull")));
		}
	}

}

void USessionHandlerMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Host Button Clicked")));
	}

	if (SessionHandlerSubsystem)
	{
		SessionHandlerSubsystem->CreateSession(NumPublicConnections, MatchType);
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");
		}
	}
}

void USessionHandlerMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1 ,15.f , FColor::Yellow, FString(TEXT("Join Button Clicked"))
		);
	}
}

void USessionHandlerMenu::MenuTearDown()
{
	RemoveFromParent();
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}

}
