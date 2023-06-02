// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ExCoreTypes.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCommand
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY()
		FString Operation;
	UPROPERTY()
		int32 Parametr;

	FCommand(FString _op, int32 _param) : Operation(_op), Parametr(_param) {}
	FCommand() {}

	FString& GetOperator()  { return Operation; }
	int32 GetParametr()  { return Parametr; }
};


UENUM()
enum class EExGameStatus : uint8
{
	GameInProgress = 0,
	ProgramInput,
	Compile
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStatusChangedSignature, EExGameStatus);

USTRUCT(BlueprintType)
struct FMovingData
{
	
	GENERATED_USTRUCT_BODY();

	//Начальная и конечная позиции параболического движения (прыжка Кузнечика)
	FVector CurrentStartPosition;
	FVector CurrentEndPosition;
	//Коэффициенты квадратного уравнения Y=AX^2+BX+C
	float A;
	float B;
	float C;
	float X; //текущая позиция по OX
	int32 Direction; // -1 back     1 forward
	int32 CurrentCommandIndex;
	TArray<FCommand> CurrentComandsArray;
};