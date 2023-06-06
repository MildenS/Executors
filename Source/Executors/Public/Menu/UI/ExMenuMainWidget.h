// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExMenuMainWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class EXECUTORS_API UExMenuMainWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* FirstLevelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SecondLevelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ThirdLevelButton;

public:

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnFirstLevelButtonPressed();

	UFUNCTION()
	void OnSecondLevelButtonPressed();

	UFUNCTION()
	void OnThirdLevelButtonPressed();


};
