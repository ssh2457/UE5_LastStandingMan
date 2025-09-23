// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FindSessionsCallbackProxy.h"
#include "Blueprint/UserWidget.h"
#include "RoomItemWidget.generated.h"

class UTextBlock;
class UButton;

/**
 *
 */
UCLASS()
class LASTMANSTANDING_API URoomItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInfo(FBlueprintSessionResult Result);

	UFUNCTION(BlueprintCallable)
	void RefreshUI();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	TObjectPtr<UTextBlock> Txt_RoomName;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	TObjectPtr<UTextBlock> Txt_PlayerCount;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	TObjectPtr<UTextBlock> Txt_MapName;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	TObjectPtr<UButton> Btn_Join;

protected:
	UPROPERTY(BlueprintReadOnly)
	FBlueprintSessionResult Result;
};
