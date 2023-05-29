// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExCoreTypes.h"
#include "ExGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EXECUTORS_API AExGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AExGameModeBase();
	FOnGameStatusChangedSignature OnGameStatusChanged;
	virtual void StartPlay() override;
	void SetGameStatus(EExGameStatus GameStatus);

private:
	EExGameStatus CurrentGameStatus = EExGameStatus::GameInProgress;

	
};
