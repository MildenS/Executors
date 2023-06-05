// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExLevelCompleteWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class EXECUTORS_API UExLevelCompleteWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void GoToMainMenu();
};
