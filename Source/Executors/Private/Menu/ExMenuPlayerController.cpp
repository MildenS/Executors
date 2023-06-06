// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/ExMenuPlayerController.h"


void AExMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}