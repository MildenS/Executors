// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExLevelFailed.h"
#include"Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Executors/Executor.h"


void UExLevelFailed::NativeConstruct()
{
	Super::NativeConstruct();

	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UExLevelFailed::GoToMainMenu);
	RetryButton->OnClicked.AddUniqueDynamic(this, &UExLevelFailed::RetryLevel);
}

void UExLevelFailed::GoToMainMenu()
{

}

void UExLevelFailed::RetryLevel()
{
	//AExecutor* Executor = nullptr;
	//for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	//{
	//	UPROPERTY()
	//		APawn* Pawn = It->Get();
	//	if (Pawn->IsPlayerControlled())
	//	{
	//		Executor = Cast<AExecutor>(Pawn);
	//		//UE_LOG(ProgramInputLog, Error, TEXT("Executor has been finded"));
	//		break;
	//	}
	//}
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(Executor);

	if (GetWorld())
	{
		FString LevelNameString = GetWorld()->GetName();
		FName LevelName = FName(*LevelNameString);
		UGameplayStatics::OpenLevel(this, LevelName, false);
	}

	
}