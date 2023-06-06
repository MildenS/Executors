// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EXECUTORS_API UExGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
		FName MenuLevelName = "MenuLevel";
	UPROPERTY(EditDefaultsOnly)
		FName FirstLevelName = "Level1";
	UPROPERTY(EditDefaultsOnly)
		FName SecondLevelName = "Level2";
	UPROPERTY(EditDefaultsOnly)
		FName ThirdLevelName = "Level3";

public:
	FName GetFirstLevelName() { return FirstLevelName; }
	FName GetSecondLevelName() { return SecondLevelName; }
	FName GetThirdLevelName() { return ThirdLevelName; }
	FName GetMenuLevelName() { return MenuLevelName; }

};
