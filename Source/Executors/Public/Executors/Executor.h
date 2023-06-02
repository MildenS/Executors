// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ExCoreTypes.h"
#include "Executor.generated.h"


struct FCommand;

UCLASS()
class EXECUTORS_API AExecutor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExecutor();
	virtual void ExecuteProgram(const TArray<FCommand>& CompiledProgram) {};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move() {};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
