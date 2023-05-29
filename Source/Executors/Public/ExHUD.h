// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExCoreTypes.h"
#include "ExHUD.generated.h"


/**
 * 
 */
UCLASS()
class EXECUTORS_API AExHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> ProgramInputWidgetClass;

private:
	UUserWidget* ProgramInputWidget;
	UFUNCTION()
	void OnGameStatusChanged(EExGameStatus GameStatus);
};
