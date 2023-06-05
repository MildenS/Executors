// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExLevelFailed.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class EXECUTORS_API UExLevelFailed : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RetryButton;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void GoToMainMenu();

	UFUNCTION()
	void RetryLevel();
};
