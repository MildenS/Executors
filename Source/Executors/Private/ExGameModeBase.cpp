// Fill out your copyright notice in the Description page of Project Settings.


#include "ExGameModeBase.h"
#include "ExHUD.h"


DEFINE_LOG_CATEGORY_STATIC(ExGameModeLog, All, All);


AExGameModeBase::AExGameModeBase()
{
	HUDClass = AExHUD::StaticClass();
}

void AExGameModeBase::StartPlay()
{
	Super::StartPlay();
	CurrentGameStatus =EExGameStatus::GameInProgress;
}


void AExGameModeBase::SetGameStatus(EExGameStatus GameStatus)
{
	if (GameStatus == CurrentGameStatus)
		return;
	if (GameStatus == EExGameStatus::EndOfLevel)
		CheckCompleteLevel();
	CurrentGameStatus = GameStatus;
	OnGameStatusChanged.Broadcast(CurrentGameStatus);
}


void AExGameModeBase::CheckCompleteLevel()
{
	if (CurrentExecutorPosition == EndPosition)
	{
		CurrentGameStatus = EExGameStatus::LevelComplete;
		UE_LOG(ExGameModeLog, Warning, TEXT("LEVEL COMPLETE!!!!, Executor position: %i"), CurrentExecutorPosition);
	}	
	else
	{
		CurrentGameStatus = EExGameStatus::LevelFailed;
		UE_LOG(ExGameModeLog, Warning, TEXT("LEVEL FAILED :(((((((((, Executor position: %i"), CurrentExecutorPosition);
	}
	OnGameStatusChanged.Broadcast(CurrentGameStatus);
}