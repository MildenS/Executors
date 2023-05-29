// Fill out your copyright notice in the Description page of Project Settings.


#include "ExGameModeBase.h"
#include "ExHUD.h"

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
	CurrentGameStatus = GameStatus;
	OnGameStatusChanged.Broadcast(CurrentGameStatus);
}
