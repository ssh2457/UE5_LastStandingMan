// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/UI/LobbyUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Lobby/Contents/LobbyPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LobbyWidget.h"


void ULobbyUserWidget::SetInfo(ALobbyPlayerState* InPlayerState)
{
	PlayerState = InPlayerState;
	RefreshUI();
}

void ULobbyUserWidget::RefreshUI()
{
	if (PlayerState == nullptr) {
		return;
	}

	// Cache Local Variable
	bool isReady = PlayerState->Ready;
	bool isServer = UKismetSystemLibrary::IsServer(this);
	bool isLocalPlayer = false;

	APlayerController* PlayerController = PlayerState->GetPlayerController();

	if (PlayerController) {
		isLocalPlayer = PlayerController->IsLocalController();
	}

	// Hide UI
	Btn_Ready->SetVisibility(ESlateVisibility::Hidden);
	Btn_KickPlayer->SetVisibility(ESlateVisibility::Hidden);
	Txt_Ready->SetVisibility(ESlateVisibility::Hidden);
	Txt_PlayerName->SetVisibility(ESlateVisibility::Hidden);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Hidden);

	// Show ready Text
	if (isReady) {
		Txt_Ready->SetVisibility(ESlateVisibility::Visible);
	}

	// Show Ready Button
	if (isLocalPlayer && !isReady) {
		Btn_Ready->SetVisibility(ESlateVisibility::Visible);
	}

	// Show Kick Button
	if (isServer && !isLocalPlayer) {
		Btn_KickPlayer->SetVisibility(ESlateVisibility::Visible);
	}

	// Set Nickname
	Editable_PlayerName->SetText(PlayerState->Nickname);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Visible);

	if (isReady) {
		Editable_PlayerName->SetIsReadOnly(true);
	}
	else {
		Editable_PlayerName->SetIsReadOnly(!isLocalPlayer);
	}
}