// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExLevelCompleteWidget.h"
#include "Components/Button.h"

void UExLevelCompleteWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UExLevelCompleteWidget::GoToMainMenu);

}



void UExLevelCompleteWidget::GoToMainMenu()
{

}
