// Fill out your copyright notice in the Description page of Project Settings.


#include "Executors/Executor.h"

// Sets default values
AExecutor::AExecutor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExecutor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExecutor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

