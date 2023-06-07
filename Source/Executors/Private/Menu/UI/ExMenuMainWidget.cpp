// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/ExMenuMainWidget.h"
#include"Components/Button.h"
#include "ExGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include"Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(MenuLog, All, All);

void UExMenuMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FirstLevelButton->OnClicked.AddUniqueDynamic(this, &UExMenuMainWidget::OnFirstLevelButtonPressed);
	SecondLevelButton->OnClicked.AddUniqueDynamic(this, &UExMenuMainWidget::OnSecondLevelButtonPressed);
	ThirdLevelButton->OnClicked.AddUniqueDynamic(this, &UExMenuMainWidget::OnThirdLevelButtonPressed);
	QuitGameButton->OnClicked.AddUniqueDynamic(this, &UExMenuMainWidget::OnQuitGameButtonPressed);

}

void UExMenuMainWidget::OnFirstLevelButtonPressed()
{
	if (GetWorld())
	{
		const auto GameInstance = GetWorld()->GetGameInstance<UExGameInstance>();
		if (GameInstance)
		{
			FName FirstLevelName = GameInstance->GetFirstLevelName();
			UGameplayStatics::OpenLevel(this, FirstLevelName, false);
		}
		else
			UE_LOG(MenuLog, Error, TEXT("GameInstance doesn't find!"));
	}
	else
	{
		UE_LOG(MenuLog, Error, TEXT("World doesn't find!"));
	}
	
}
void UExMenuMainWidget::OnSecondLevelButtonPressed()
{
	if (GetWorld())
	{
		const auto GameInstance = GetWorld()->GetGameInstance<UExGameInstance>();
		if (GameInstance)
		{
			FName SecondLevelName = GameInstance->GetSecondLevelName();
			UGameplayStatics::OpenLevel(this, SecondLevelName, false);
		}
		else
			UE_LOG(MenuLog, Error, TEXT("GameInstance doesn't find!"));
	}
	else
	{
		UE_LOG(MenuLog, Error, TEXT("World doesn't find!"));
	}
}
void UExMenuMainWidget::OnThirdLevelButtonPressed()
{
	if (GetWorld())
	{
		const auto GameInstance = GetWorld()->GetGameInstance<UExGameInstance>();
		if (GameInstance)
		{
			FName ThirdLevelName = GameInstance->GetThirdLevelName();
			UGameplayStatics::OpenLevel(this, ThirdLevelName, false);
		}
		else
			UE_LOG(MenuLog, Error, TEXT("GameInstance doesn't find!"));
	}
	else
	{
		UE_LOG(MenuLog, Error, TEXT("World doesn't find!"));
	}
}


void UExMenuMainWidget::OnQuitGameButtonPressed()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}