// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ExCoreTypes.generated.h"

/**
 * 
 */


UENUM()
enum class ECommandType : uint8
{
	Movement = 0,
	Loop
};

USTRUCT(BlueprintType)
struct FCommand
{
	GENERATED_USTRUCT_BODY();


	UPROPERTY()
		FString Operation;
	UPROPERTY()
		int32 Parametr;
	ECommandType CommandType;
	TArray<FCommand> LoopCommands;
	int32 LoopIterationsNum;
	int32 LoopIterator; //итератор для цикла (чтобы проходить по итерациям цикла
	int32 LoopCommandsIterator; //итератор для прохода по командам внутри одной итерации цикла
	bool IsCounted; //считалась ли команда при учёте передвижения Исполнителя в его системе координат 
	// (необходимо для верного учёта позиции Исполнителя при завершении уровня
	FCommand(FString _op, int32 _param) : Operation(_op), Parametr(_param) {}
	FCommand() {}


	bool operator == (const FCommand other) const
	{
		return (this->Operation == other.Operation) && (this->Parametr == other.Parametr);
	}

	FString& GetOperator()  { return Operation; }
	int32 GetParametr()  { return Parametr; }
};


UENUM()
enum class EExGameStatus : uint8
{
	GameInProgress = 1,
	ProgramInput,
	Compile,
	EndOfLevel,
	LevelComplete,
	LevelFailed
};




DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStatusChangedSignature, EExGameStatus);

USTRUCT(BlueprintType)
struct FMovingData
{
	
	GENERATED_USTRUCT_BODY();

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	float TimerRate;

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