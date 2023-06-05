// Fill out your copyright notice in the Description page of Project Settings.


#include "ExGameModeBase.h"
#include "ExHUD.h"
#include "ExCoreTypes.h"


DEFINE_LOG_CATEGORY_STATIC(ExGameModeLog, All, All);


AExGameModeBase::AExGameModeBase()
{
	HUDClass = AExHUD::StaticClass();
}

void AExGameModeBase::StartPlay()
{
	Super::StartPlay();
	CurrentGameStatus =EExGameStatus::GameInProgress;
	
	
	//Обрабатываем разрешённые команды
	AllowedCommands.Empty();
	TArray<FString> CommandsArray;
	const TCHAR* DelimsArray[] = { TEXT(" "), TEXT(","), TEXT("\n"), TEXT("\r"), TEXT("\b"), TEXT("\t") };
	for (FString AllowedCommand : AllowedCommandsStrings)
	{
		int32 CommandsNum = AllowedCommand.ParseIntoArray(CommandsArray, DelimsArray, 6, true);
		if (CommandsArray.Num() == 2)
		{
			FString CurrentOperator = CommandsArray[0].ToLower();
			if (CurrentOperator == "forward" || CurrentOperator == "back")
			{
				int32 CurrentParametr = FCString::Atoi(*CommandsArray[1]);
				FCommand CurrentCommand(CurrentOperator, CurrentParametr);
				CurrentCommand.CommandType = ECommandType::Movement;
				AllowedCommands.Add(CurrentCommand);
			}
		}
	}
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


TArray<FCommand>& AExGameModeBase::GetAllowedCommands()
{
	return AllowedCommands;
}