// Fill out your copyright notice in the Description page of Project Settings.


#include "Executors/Grasshopper.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ExCoreTypes.h"

AGrasshopper::AGrasshopper()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	SphereCollision->SetCollisionProfileName("Grasshopper collision");
	RootComponent = SphereCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	FillCorrectOperations();
}

void AGrasshopper::ExecuteProgram(const TArray<FCommand>& CompiledProgram)
{
	Super::ExecuteProgram(CompiledProgram);
	for (const FCommand& Command : CompiledProgram)
	{
		if (CorrectOperations.Contains(Command.Operation))
		{
			if (Command.Operation == "forward")
				Move(Command.Parametr * StepDistance);
			else if (Command.Operation == "back")
				Move(-Command.Parametr * StepDistance);
		}
	}
}



void AGrasshopper::BeginPlay()
{
	Super::BeginPlay();
}

void AGrasshopper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrasshopper::Move(int Distance)
{
	Super::Move(Distance);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Distance;
	SetActorLocation(NewLocation);
}

void AGrasshopper::FillCorrectOperations()
{
	CorrectOperations.Add("repeat");
	CorrectOperations.Add(TEXT("times"));
	CorrectOperations.Add(TEXT("end"));
	CorrectOperations.Add(TEXT("forward"));
	CorrectOperations.Add(TEXT("back")); 
}




	