// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExCoreTypes.h"
#include "ExPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXECUTORS_API AExPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    UFUNCTION()
    void OnGameStatusChanged(EExGameStatus Status);
    void OnProgramInput();
};
