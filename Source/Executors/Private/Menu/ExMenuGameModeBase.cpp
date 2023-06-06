// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/ExMenuGameModeBase.h"
#include"Menu/ExMenuPlayerController.h"
#include"Menu/UI/ExMenuHUD.h"

AExMenuGameModeBase::AExMenuGameModeBase()
{
	HUDClass = AExMenuHUD::StaticClass();
	PlayerControllerClass = AExMenuPlayerController::StaticClass();
}