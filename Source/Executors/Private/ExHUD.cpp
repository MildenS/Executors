// Fill out your copyright notice in the Description page of Project Settings.


#include "ExHUD.h"
#include "Blueprint/UserWidget.h"
#include"ExProgramInputWidget.h"
#include "ExGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogHUD, All, All);

void AExHUD::BeginPlay()
{
	Super::BeginPlay();

	ProgramInputWidget = CreateWidget<UUserWidget>(GetWorld(), ProgramInputWidgetClass);
	if (ProgramInputWidget)
	{
		ProgramInputWidget->AddToViewport();
		ProgramInputWidget->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogHUD, Error, TEXT("ProgramInputWidget create!!!!!"));
	}
	else 
		UE_LOG(LogHUD, Error, TEXT("ProgramInputWidget didn't create!!!!!"));
	

	if (GetWorld())
	{
		const auto GameMode = Cast<AExGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStatusChanged.AddUObject(this, &AExHUD::OnGameStatusChanged);
		}
	}
}


void AExHUD::OnGameStatusChanged(EExGameStatus GameStatus)
{
	if (GameStatus == EExGameStatus::ProgramInput)
	{
		if (ProgramInputWidget)
			ProgramInputWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
		ProgramInputWidget->SetVisibility(ESlateVisibility::Hidden);
}