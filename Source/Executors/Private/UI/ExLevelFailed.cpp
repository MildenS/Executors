// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExLevelFailed.h"
#include"Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Executors/Executor.h"
#include"ExGameInstance.h"


void UExLevelFailed::NativeConstruct()
{
	Super::NativeConstruct();

	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UExLevelFailed::GoToMainMenu);
	RetryButton->OnClicked.AddUniqueDynamic(this, &UExLevelFailed::RetryLevel);
}

void UExLevelFailed::GoToMainMenu()
{
	if (GetWorld())
	{
		auto GameInstance = GetWorld()->GetGameInstance<UExGameInstance>();
		FName MenuLevelName = GameInstance->GetMenuLevelName();
		UGameplayStatics::OpenLevel(this, MenuLevelName, false);
	}
}

void UExLevelFailed::RetryLevel()
{
	if (GetWorld())
	{
		FString LevelNameString = GetWorld()->GetName();
		FName LevelName = FName(*LevelNameString);
		UGameplayStatics::OpenLevel(this, LevelName, false);
	}
}