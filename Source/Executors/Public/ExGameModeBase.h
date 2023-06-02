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
	int32 GetStartPosition() { return StartPosition; }
	void SetCurrentExecutorPosition(int32 pos) { CurrentExecutorPosition = pos; }

private:
	EExGameStatus CurrentGameStatus = EExGameStatus::GameInProgress;
	void CheckCompleteLevel();
	UPROPERTY(EditAnywhere)
		int32 EndPosition=10;
	UPROPERTY(EditAnywhere)
		int32 StartPosition = 0;
	int32 CurrentExecutorPosition; //Позиция, на которой остановился Исполнитель (в системе координат Исполнителя)
};
