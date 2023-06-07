// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExLevelCompleteWidget.h"
#include "Components/Button.h"
#include"ExGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UExLevelCompleteWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UExLevelCompleteWidget::GoToMainMenu);

}



void UExLevelCompleteWidget::GoToMainMenu()
{
	if (GetWorld())
	{
		auto GameInstance = GetWorld()->GetGameInstance<UExGameInstance>();
		FName MenuLevelName = GameInstance->GetMenuLevelName();
		UGameplayStatics::OpenLevel(this, MenuLevelName, false);
	}
}
