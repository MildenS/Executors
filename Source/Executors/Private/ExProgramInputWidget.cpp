// Fill out your copyright notice in the Description page of Project Settings.


#include "ExProgramInputWidget.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableText.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "ExCoreTypes.h"
#include "Executors/Executor.h"
#include "ExGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(ProgramInputLog, All, All);

void UExProgramInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CompileButton->OnClicked.AddUniqueDynamic(this, &UExProgramInputWidget::CompileProgram);
}

void UExProgramInputWidget::CompileProgram()
{
	UE_LOG(ProgramInputLog, Error, TEXT("Starting compile program"));
	TArray<FCommand> CompiledProgram;
	//UE_LOG(ProgramInputLog, Error, TEXT("Length of the program = %i"), ProgramInputField->GetText().ToString().Len());
	FString Program = ProgramInputField->GetText().ToString();
	TArray<FString> CommandsArray;
	/*TUniquePtr<TCHAR[]> DelimsArray(new TCHAR[2]);
	DelimsArray[0] = TCHAR(' ');
	DelimsArray[1] = TCHAR(',');*/
	const TCHAR* DelimsArray[] = { TEXT(" "), TEXT(","), TEXT("\n"), TEXT("\r"), TEXT("\b"), TEXT("\t") };
	if (!Program.IsEmpty())
	{
		int32 CommandsNum = Program.ParseIntoArray(CommandsArray, DelimsArray, 6,  true);
		for (int32 i = 0; i < CommandsArray.Num(); i += 2)
		{
			UE_LOG(ProgramInputLog, Error, TEXT("Command №%i   %s, %s"), i+1, *CommandsArray[i], *CommandsArray[i+1]);
		}
		if (CommandsArray.Num()>1)
		{
			int32 i = 0;
			while (i < CommandsArray.Num())
			{
				UE_LOG(ProgramInputLog, Error, TEXT("Starting work under program text"));
				FString CurrentOperator = CommandsArray[i].ToLower();
				int32 CurrentParametr = FCString::Atoi(*CommandsArray[i + 1]);
				FCommand CurrentCommand(CurrentOperator, CurrentParametr);
				CompiledProgram.Add(CurrentCommand);
				i += 2;
			}
		}
		UE_LOG(ProgramInputLog, Error, TEXT("Program has been compiled"));
		UE_LOG(ProgramInputLog, Error, TEXT("Number of Commands = %i"), CompiledProgram.Num());
		//закомменчено, пока не создам класс Исполнитля
		UPROPERTY()
			AExecutor* Executor = FindExecutor();
		if (GetWorld())
		{
			const auto GameMode = Cast<AExGameModeBase>(GetWorld()->GetAuthGameMode());
			GameMode->SetGameStatus(EExGameStatus::GameInProgress);
		}
		if (Executor)
			Executor->ExecuteProgram(CompiledProgram);
		
	}
}

//закомменчено, пока не создам класс исполнителя
AExecutor* UExProgramInputWidget::FindExecutor()
{
	UPROPERTY()
	AExecutor* Executor = nullptr;
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		UPROPERTY()
		APawn* Pawn = It->Get();
		if (Pawn->IsPlayerControlled())
		{
			Executor = Cast<AExecutor>(Pawn);
			UE_LOG(ProgramInputLog, Error, TEXT("Executor has been finded"));
			break;
		}
	}
	return Executor;
}