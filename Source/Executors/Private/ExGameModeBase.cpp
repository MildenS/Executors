// Fill out your copyright notice in the Description page of Project Settings.


#include "ExGameModeBase.h"
#include "ExHUD.h"

AExGameModeBase::AExGameModeBase()
{
	HUDClass = AExHUD::StaticClass();
}
