// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Executors/Executor.h"
#include "Grasshopper.generated.h"


class UCameraComponent;
class USphereComponent;

/**
 * 
 */
UCLASS()
class EXECUTORS_API AGrasshopper : public AExecutor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AGrasshopper();
	virtual void ExecuteProgram(const TArray<FCommand>& CompiledProgram) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, Category = "Movement Parametrs")
		int32 StepDistance = 5;

	UPROPERTY(EditAnywhere, Category = "Movement Parametrs")
		int32 JumpHeight = 10;

	UPROPERTY(EditAnywhere, Category = "Movement Parametrs")
		int32 MovesInOneStep = 5; //Количество мини-шагов по перемещению на 1

	virtual void Move() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:


	//для отладки таймеров (на работу игры не влияет)
	int32 timerCounter;

	UPROPERTY()
	TSet<FString> CorrectOperations;
	void FillCorrectOperations();
	void DelayFunction();

	FMovingData CurrentMovingData;
	int32 CurrentExecutorPosition = 0; //Текущая позиция в системе координат Исполнителя

	/*float StepX = 0;
	float StepY = 0;*/
	//bool UpFlag;
};
