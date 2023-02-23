// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionHandlerMenu.generated.h"

/**
 * 
 */
class UButton;
class USessionHandlerSubsystem;

UCLASS()
class SESSIONHANDLER_API USessionHandlerMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void MenuSetup(int32 NumberOfPublicConnecions=4,FString TypeOfMatch =FString(TEXT("FreeForAll")));
protected:

	virtual bool Initialize() override;

	virtual void NativeDestruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();
	// The subsystem designed to handle all online session functionality
	USessionHandlerSubsystem* SessionHandlerSubsystem;

	int32 NumPublicConnections{ 4 };
	FString MatchType{ TEXT("FreeForAll") };
};
