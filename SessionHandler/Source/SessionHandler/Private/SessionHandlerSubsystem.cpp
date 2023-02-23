// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionHandlerSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

USessionHandlerSubsystem::USessionHandlerSubsystem():
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}


void USessionHandlerSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	if (!SessionInterface.IsValid()) return;

	//check if session exist and destroy if so, becose we need to have no session to create one
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}
	//delegate to activate after completion of communication with server, stored in a delegateHandle
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	// If subsystem is null it is a lan, if eq STEAM it is not lan;
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true:false;
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	// if session is not created successfull, destroy handle
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCancelFindSessionsCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
}

void USessionHandlerSubsystem::FindSessions(int32 MaxSearchResults)
{
}

void USessionHandlerSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

void USessionHandlerSubsystem::DestroySession()
{
}

void USessionHandlerSubsystem::StartSession()
{
}

void USessionHandlerSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void USessionHandlerSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void USessionHandlerSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void USessionHandlerSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void USessionHandlerSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}