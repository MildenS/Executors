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
	UPROPERTY()
	UCameraComponent* Camera;
	UPROPERTY()
	UStaticMeshComponent* Mesh;
	UPROPERTY()
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, Category = "Movement Parametrs")
		int32 StepDistance = 50;

	virtual void Move(int Distance) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY()
	TSet<FString> CorrectOperations;
	void FillCorrectOperations();

};
