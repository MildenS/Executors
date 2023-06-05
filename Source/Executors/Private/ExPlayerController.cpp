// Fill out your copyright notice in the Description page of Project Settings.


#include "ExPlayerController.h"
#include "ExGameModeBase.h"

void AExPlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (GetWorld())
    {
        if (const auto GameMode = Cast<AExGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnGameStatusChanged.AddUObject(this, &AExPlayerController::OnGameStatusChanged);
        }
    }
}

void AExPlayerController::OnGameStatusChanged(EExGameStatus Status)
{
    if (Status == EExGameStatus::ProgramInput)
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
    else if (Status == EExGameStatus::LevelComplete)
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
    else if (Status == EExGameStatus::LevelFailed)
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void AExPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    InputComponent->BindAction("InputProgram", IE_Pressed, this, &AExPlayerController::OnProgramInput);
}

void AExPlayerController::OnProgramInput()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    const auto GameMode = Cast<AExGameModeBase>(GetWorld()->GetAuthGameMode());
    GameMode->SetGameStatus(EExGameStatus::ProgramInput);
}