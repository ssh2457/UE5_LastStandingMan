// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/Contents/LobbyPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyPlayerState.h"
#include "LobbyGameMode.h"

void ALobbyPlayerController::Server_HandleReadyButton_Implementation()
{
	if (!UKismetSystemLibrary::IsServer(this)) {
		return;
	}

	ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(GetPawn()->GetPlayerState());
	if (LobbyPlayerState) {
		LobbyPlayerState->Multicast_Ready();

		ALobbyGameMode* LobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(this));
		if (LobbyGameMode) {
			LobbyGameMode->TryStartGame();
		}
	}
}

void ALobbyPlayerController::Server_HandleChangeNickname_Implementation(const FText& InNickname)
{
	if (!UKismetSystemLibrary::IsServer(this)) {
		return;
	}

	ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(GetPawn()->GetPlayerState());
	if (LobbyPlayerState) {
		LobbyPlayerState->Nickname = InNickname;
	}
}