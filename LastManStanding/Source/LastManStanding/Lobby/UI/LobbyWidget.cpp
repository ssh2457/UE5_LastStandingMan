// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/UI/LobbyWidget.h"
#include "LobbyUserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Lobby/Contents/LobbyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameState.h"

bool ULobbyWidget::Initialize()
{
	if (Super::Initialize() == false) {
		return false;
	}

	SetInfo();

	return true;
}

void ULobbyWidget::SetInfo()
{
	// Clear Children
	UserList->ClearChildren();
	LobbyUsers.Empty();

	// Create child Widget
	for (int32 i = 0; i < 10; ++i) {
		if (LobbyUserWidgetClass == nullptr) {
			continue;
		}

		ULobbyUserWidget* ChildWidget = CreateWidget<ULobbyUserWidget>(GetWorld(), LobbyUserWidgetClass);
		if (ChildWidget == nullptr) {
			continue;
		}

		UserList->AddChildToVerticalBox(ChildWidget);
		LobbyUsers.Add(ChildWidget);
	}

	RefreshUI();
}

void ULobbyWidget::RefreshUI()
{
	AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
	if (GameState == nullptr) {
		return;
	}

	// Cache Player Length
	TArray<ALobbyPlayerState*> LobbyPlayerStates = GetLobbyPlayerStates();
	const int32 PlayerLength = LobbyPlayerStates.Num();

	for (int32 i = 0; i < LobbyUsers.Num(); ++i) {
		const int32 Index = i;

		if (Index < PlayerLength) {
			// Show UI
			LobbyUsers[Index]->SetVisibility(ESlateVisibility::Visible);

			// SetInfo
			ALobbyPlayerState* PlayerState = GetLobbyPlayerStateAtIndex(Index);
			LobbyUsers[Index]->SetInfo(PlayerState);
		}
		else {
			// Hide UI
			LobbyUsers[Index]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	// Config UI
	if (UKismetSystemLibrary::IsServer(this)) {
		Btn_GameConfig->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Btn_GameConfig->SetVisibility(ESlateVisibility::Collapsed);
	}
}

TArray<ALobbyPlayerState*> ULobbyWidget::GetLobbyPlayerStates()
{
	TArray<ALobbyPlayerState*> LobbyPlayerStates;

	AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
	if (GameState) {
		for (TObjectPtr<APlayerState> PlayerState : GameState->PlayerArray) {
			ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
			if (LobbyPlayerState) {
				LobbyPlayerStates.Add(LobbyPlayerState);
			}
		}
	}

	return LobbyPlayerStates;
}

ALobbyPlayerState* ULobbyWidget::GetLobbyPlayerStateAtIndex(const int32 InIndex)
{
	TArray<ALobbyPlayerState*> LobbyPlayerStates = GetLobbyPlayerStates();
	if (InIndex < LobbyPlayerStates.Num()) {
		return LobbyPlayerStates[InIndex];
	}
	return nullptr;
}
