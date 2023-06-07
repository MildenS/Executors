// Fill out your copyright notice in the Description page of Project Settings.


#include "ExPlayerController.h"
#include "ExGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(ExPlayerControllerLog, All, All);

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
    if (Status == EExGameStatus::GameInProgress)
    {
        SetInputMode(FInputModeGameOnly());
        UE_LOG(ExPlayerControllerLog, Warning, TEXT("Input mode = GameOnly"));
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        UE_LOG(ExPlayerControllerLog, Warning, TEXT("Input mode = UIOnly"));
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