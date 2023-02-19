// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionHandlerSubsystem.h"
#include "OnlineSubsystem.h"


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