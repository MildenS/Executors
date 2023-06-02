// Fill out your copyright notice in the Description page of Project Settings.


#include "Executors/Grasshopper.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include"ExGameModeBase.h"
#include "ExCoreTypes.h"

DEFINE_LOG_CATEGORY_STATIC(GrasshopperLog, All, All);

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
	for (int32 i = 0; i < CurrentMovingData.CurrentComandsArray.Num(); i++)
	{
		CurrentMovingData.CurrentComandsArray.RemoveAt(i);
	}
	for (FCommand Command :CompiledProgram)
	{
		if(CorrectOperations.Contains(Command.GetOperator()))
			CurrentMovingData.CurrentComandsArray.Add(Command);
	}
	CurrentMovingData.CurrentCommandIndex = 0;
	Move();
}



void AGrasshopper::BeginPlay()
{
	Super::BeginPlay();
}

void AGrasshopper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void AGrasshopper::Move(int Distance)
//{
//	float TimerRate = 5.f;
//	FTimerHandle TimerHandle;
//	Super::Move(Distance);
//	int32 MovesCount = abs(Distance) * MovesInOneStep;
//	//int32 MovesToMaxHeight = JumpHeight / (MovesCount / 2);
//	float StepX = StepDistance / MovesInOneStep;
//	StepX *= Distance < 0 ? (-1) : 1;
//	float StepY = JumpHeight / (MovesCount / 2);
//
//	for (int32 i = 0; i < MovesCount/2; i++)
//	{
//		FVector NewLocation = GetActorLocation();
//		NewLocation.X += StepX;
//		NewLocation.Y += StepY;
//		SetActorLocation(NewLocation);
//		GetWorldTimerManager().SetTimer(TimerHandle, TimerRate, false);
//	}
//	for (int32 i = 0; i < MovesCount/2; i++)
//	{
//		FVector NewLocation = GetActorLocation();
//		NewLocation.X += StepX;
//		NewLocation.Y -= StepY;
//		SetActorLocation(NewLocation);
//		GetWorldTimerManager().SetTimer(TimerHandle, TimerRate, false);
//	}
//	
//}


void AGrasshopper::Move()
{
	//IsMoving = true;
	if (CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].CommandType == ECommandType::Movement)
	{
		CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].IsCounted = false;
		int32 Distance = CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].GetParametr();
		if (CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].GetOperator() == TEXT("forward"))
		{
			CurrentMovingData.Direction = 1;
		}
		else
		{
			CurrentMovingData.Direction = -1;
		}
		CurrentMovingData.CurrentStartPosition = GetActorLocation();
		CurrentMovingData.CurrentEndPosition =
			FVector((CurrentMovingData.CurrentStartPosition.X + Distance * StepDistance * CurrentMovingData.Direction),
				CurrentMovingData.CurrentStartPosition.Y, CurrentMovingData.CurrentStartPosition.Z);

		// Рассчитываем вершину параболы
		float MidX = (CurrentMovingData.CurrentStartPosition.X + CurrentMovingData.CurrentEndPosition.X) / 2.f;
		float MaxY = JumpHeight;
		FVector VertexPos = FVector(MidX, MaxY, 0.f);

		float y0 = VertexPos.Y;
		float y1 = CurrentMovingData.CurrentStartPosition.Y;
		float y2 = CurrentMovingData.CurrentEndPosition.Y;
		float x0 = VertexPos.X;
		float x1 = CurrentMovingData.CurrentStartPosition.X;
		float x2 = CurrentMovingData.CurrentEndPosition.X;

		CurrentMovingData.A = ((y2 - y1) * (x1 - x0) - (y1 - y0) * (x2 - x1)) / ((x1 - x0) * (x2 * x2 - x1 * x1) - (x2 - x1) * (x1 * x1 - x0 * x0));
		CurrentMovingData.B = ((y1 - y0) - CurrentMovingData.A * (x1 * x1 - x0 * x0)) / (x1 - x0);
		CurrentMovingData.C = y0 - CurrentMovingData.A * x0 * x0 - CurrentMovingData.B * x0;

		UE_LOG(GrasshopperLog, Error, TEXT("A = %f   B = %f     C = %f"), CurrentMovingData.A, CurrentMovingData.B, CurrentMovingData.C);

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;

		CurrentMovingData.X = CurrentMovingData.CurrentStartPosition.X;
		TimerDelegate.BindLambda([&]
			{
				if (CurrentMovingData.Direction > 0 && CurrentMovingData.X > CurrentMovingData.CurrentEndPosition.X
					|| CurrentMovingData.Direction < 0 && CurrentMovingData.X < CurrentMovingData.CurrentEndPosition.X)
				{
					if (CurrentMovingData.CurrentCommandIndex < CurrentMovingData.CurrentComandsArray.Num())
					{
						CurrentExecutorPosition += CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].GetParametr();
						UE_LOG(GrasshopperLog, Warning, TEXT("Grasshopper position: %i"), CurrentExecutorPosition);
						CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].IsCounted = true;
					}					
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					CurrentMovingData.CurrentCommandIndex += 1;
					//IsMoving = false;
					if (CurrentMovingData.CurrentCommandIndex < CurrentMovingData.CurrentComandsArray.Num())
						Move();
					if (CurrentMovingData.CurrentCommandIndex >= CurrentMovingData.CurrentComandsArray.Num())
					{
						if (GetWorld())
						{
							auto GameMode = Cast<AExGameModeBase>(GetWorld()->GetAuthGameMode());
							//UE_LOG(GrasshopperLog, Warning, TEXT("Finally Grasshopper position:  %i"), CurrentExecutorPosition);
							GameMode->SetCurrentExecutorPosition(CurrentExecutorPosition);
							GameMode->SetGameStatus(EExGameStatus::EndOfLevel);	
						}
					}
					return;
				}
				// Интерполируем значения по оси X и вычисляем соответствующие значения по оси Y
				float Y = CurrentMovingData.A * FMath::Square(CurrentMovingData.X) + CurrentMovingData.B * CurrentMovingData.X + CurrentMovingData.C;
				FVector NewPosition = FVector(CurrentMovingData.X, Y, CurrentMovingData.CurrentStartPosition.Z);
				UE_LOG(GrasshopperLog, Warning, TEXT("NewPosition.X = %f     NewPosition.Y = %f"), NewPosition.X, NewPosition.Y);
				CurrentMovingData.X += 1.f * CurrentMovingData.Direction;
				// Обновляем позицию меша
				SetActorLocation(NewPosition);
			});

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.01f, true);
	}
	
	else if (CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].CommandType == ECommandType::Loop)
	{
		FCommand CurrentLoopCommand = 
		CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommands[CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator];
		CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommands[CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator].IsCounted=false;
		UE_LOG(GrasshopperLog, Warning, TEXT("Loop command:  %s   %i"), *CurrentLoopCommand.GetOperator(), CurrentLoopCommand.GetParametr());
		int32 Distance = CurrentLoopCommand.GetParametr();
		if (CurrentLoopCommand.GetOperator() == TEXT("forward"))
		{
			CurrentMovingData.Direction = 1;
		}
		else
		{
			CurrentMovingData.Direction = -1;
		}
		CurrentMovingData.CurrentStartPosition = GetActorLocation();
		CurrentMovingData.CurrentEndPosition =
			FVector((CurrentMovingData.CurrentStartPosition.X + Distance * StepDistance * CurrentMovingData.Direction),
				CurrentMovingData.CurrentStartPosition.Y, CurrentMovingData.CurrentStartPosition.Z);

		// Рассчитываем вершину параболы
		float MidX = (CurrentMovingData.CurrentStartPosition.X + CurrentMovingData.CurrentEndPosition.X) / 2.f;
		float MaxY = JumpHeight;
		FVector VertexPos = FVector(MidX, MaxY, 0.f);

		float y0 = VertexPos.Y;
		float y1 = CurrentMovingData.CurrentStartPosition.Y;
		float y2 = CurrentMovingData.CurrentEndPosition.Y;
		float x0 = VertexPos.X;
		float x1 = CurrentMovingData.CurrentStartPosition.X;
		float x2 = CurrentMovingData.CurrentEndPosition.X;

		CurrentMovingData.A = ((y2 - y1) * (x1 - x0) - (y1 - y0) * (x2 - x1)) / ((x1 - x0) * (x2 * x2 - x1 * x1) - (x2 - x1) * (x1 * x1 - x0 * x0));
		CurrentMovingData.B = ((y1 - y0) - CurrentMovingData.A * (x1 * x1 - x0 * x0)) / (x1 - x0);
		CurrentMovingData.C = y0 - CurrentMovingData.A * x0 * x0 - CurrentMovingData.B * x0;

		//UE_LOG(GrasshopperLog, Error, TEXT("A = %f   B = %f     C = %f"), CurrentMovingData.A, CurrentMovingData.B, CurrentMovingData.C);

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;

		CurrentMovingData.X = CurrentMovingData.CurrentStartPosition.X;
		TimerDelegate.BindLambda([&]
			{
				if (CurrentMovingData.Direction > 0 && CurrentMovingData.X > CurrentMovingData.CurrentEndPosition.X
					|| CurrentMovingData.Direction < 0 && CurrentMovingData.X < CurrentMovingData.CurrentEndPosition.X)
				{
					if (CurrentMovingData.CurrentCommandIndex < CurrentMovingData.CurrentComandsArray.Num()
						&& CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator < CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommands.Num()
						&& CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopIterator < CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopIterationsNum)
					{
						CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommands[CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator].IsCounted = true;
						CurrentExecutorPosition += CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommands[CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator].GetParametr();
					}
					if (CurrentMovingData.CurrentCommandIndex >= CurrentMovingData.CurrentComandsArray.Num())
					{
						if (GetWorld())
						{
							auto GameMode = Cast<AExGameModeBase>(GetWorld()->GetAuthGameMode());
							GameMode->SetCurrentExecutorPosition(CurrentExecutorPosition);
							GameMode->SetGameStatus(EExGameStatus::EndOfLevel);
						}
						return;
					}
					
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					//переход на следующую команду цикла

					CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator += 1;
					//если дошёл до конца одной итерации цикла, то перехожу на следующую
					if (CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator < CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommands.Num())
					{
						Move();
					}
					else
					{
						CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopIterator += 1;
						
						if (CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopIterator < CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopIterationsNum)
						{
							CurrentMovingData.CurrentComandsArray[CurrentMovingData.CurrentCommandIndex].LoopCommandsIterator = 0;
							Move();
						}
						else
						{
							CurrentMovingData.CurrentCommandIndex += 1;
							if (CurrentMovingData.CurrentCommandIndex < CurrentMovingData.CurrentComandsArray.Num())
								Move();				
							return;
						}
							
					}
				}
				// Интерполируем значения по оси X и вычисляем соответствующие значения по оси Y
				float Y = CurrentMovingData.A * FMath::Square(CurrentMovingData.X) + CurrentMovingData.B * CurrentMovingData.X + CurrentMovingData.C;
				FVector NewPosition = FVector(CurrentMovingData.X, Y, CurrentMovingData.CurrentStartPosition.Z);
				//UE_LOG(GrasshopperLog, Warning, TEXT("NewPosition.X = %f     NewPosition.Y = %f"), NewPosition.X, NewPosition.Y);
				CurrentMovingData.X += 1.f * CurrentMovingData.Direction;
				// Обновляем позицию меша
				SetActorLocation(NewPosition);
			});

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.01f, true);
	}	
}

void AGrasshopper::FillCorrectOperations()
{
	CorrectOperations.Add(TEXT("repeat"));
	CorrectOperations.Add(TEXT("times"));
	CorrectOperations.Add(TEXT("end"));
	CorrectOperations.Add(TEXT("forward"));
	CorrectOperations.Add(TEXT("back")); 
}


//void AGrasshopper::DelayFunction()
//{
//	DelayFlag = !DelayFlag;
//}

	
//void AGrasshopper::Move(int Distance)
//{
//	float TimerRate = 5.f;
//	Super::Move(Distance);
//	int32 MovesCount = abs(Distance) * MovesInOneStep;
//	//int32 MovesToMaxHeight = JumpHeight / (MovesCount / 2);
//	StepX = (float)StepDistance / (float)MovesInOneStep;
//	StepX *= Distance < 0 ? (-1) : 1;
//	StepY = (float)JumpHeight / ((float)MovesCount / 2.0);
//	UE_LOG(GrasshopperLog, Warning, TEXT("StepX = %f StepY = %f   MovesCount = %d"), StepX, StepY, MovesCount);
//	UpFlag = true;
//	FTimerHandle TimerHandleUp;
//	FTimerDelegate TimerDelegateUp;
//	FTimerHandle TimerHandleDown;
//	FTimerDelegate TimerDelegateDown;
//	int i = 0;
//	TimerDelegateUp.BindLambda([&]
//		{
//			if (i > MovesCount / 2) { GetWorld()->GetTimerManager().ClearTimer(TimerHandleUp); UpFlag = false; return; }
//
//			// YOUR CODE HERE
//			if (UpFlag)
//			{
//				UE_LOG(GrasshopperLog, Warning, TEXT("Move UP"));
//				FVector NewLocation = GetActorLocation();
//				NewLocation.X += StepX;
//				NewLocation.Y += StepY;
//				SetActorLocation(NewLocation);
//				UE_LOG(GrasshopperLog, Warning, TEXT("New Coordinates: %f   %f"), NewLocation.X, NewLocation.Y);
//				UE_LOG(GrasshopperLog, Warning, TEXT("StepX = %f StepY = %f"), StepX, StepY);
//				i++;
//			}
//
//		});
//
//	GetWorld()->GetTimerManager().SetTimer(TimerHandleUp, TimerDelegateUp, 0.001f, true);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
//
//	int j = 0;
//	TimerDelegateDown.BindLambda([&]
//		{
//			if (i > MovesCount / 2) { GetWorld()->GetTimerManager().ClearTimer(TimerHandleDown); return; }
//
//			// YOUR CODE HERE
//			if (!UpFlag)
//			{
//				UE_LOG(GrasshopperLog, Warning, TEXT("Move down"));
//				FVector NewLocation = GetActorLocation();
//				NewLocation.X += StepX;
//				NewLocation.Y -= StepY;
//				SetActorLocation(NewLocation);
//				UE_LOG(GrasshopperLog, Warning, TEXT("New Coordinates: %f   %f"), NewLocation.X, NewLocation.Y);
//				j++;
//			}
//
//		});
//
//	GetWorld()->GetTimerManager().SetTimer(TimerHandleDown, TimerDelegateDown, 0.001f, true);
//
//
//}