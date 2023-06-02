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
	FString Program = ProgramInputField->GetText().ToString();
	TArray<FString> CommandsArray;
	const TCHAR* DelimsArray[] = { TEXT(" "), TEXT(","), TEXT("\n"), TEXT("\r"), TEXT("\b"), TEXT("\t") };
	if (!Program.IsEmpty())
	{
		int32 CommandsNum = Program.ParseIntoArray(CommandsArray, DelimsArray, 6,  true);
		if (CommandsArray.Num()>1)
		{
			int32 i = 0;
			while (i < CommandsArray.Num())
			{
				UE_LOG(ProgramInputLog, Error, TEXT("Starting work under program text"));
				FString CurrentOperator = CommandsArray[i].ToLower();
				if (CurrentOperator == "forward" || CurrentOperator == "back")
				{
					int32 CurrentParametr = FCString::Atoi(*CommandsArray[i + 1]);
					FCommand CurrentCommand(CurrentOperator, CurrentParametr);
					CurrentCommand.CommandType = ECommandType::Movement;
					CompiledProgram.Add(CurrentCommand);
					i += 2;
				}
				else if (CurrentOperator == "repeat")
				{
					int32 CurrentParametr = FCString::Atoi(*CommandsArray[i + 1]);
					FCommand CurrentCommand(CurrentOperator, CurrentParametr);
					CurrentCommand.CommandType = ECommandType::Loop;
					CurrentCommand.LoopIterationsNum = CurrentParametr;
					CurrentCommand.LoopCommandsIterator = 0;
					CurrentCommand.LoopIterator = 0;
					i += 3;
					FString CurrentLoopOperator = CommandsArray[i].ToLower();
					while (CurrentLoopOperator != "end")
					{
						int32 CurrentLoopParametr = FCString::Atoi(*CommandsArray[i + 1]);
						UE_LOG(ProgramInputLog, Error, TEXT("Loop command: %s  %i"), *CurrentLoopOperator, CurrentLoopParametr);
						FCommand CurrentLoopCommand(CurrentLoopOperator, CurrentLoopParametr);
						CurrentLoopCommand.CommandType = ECommandType::Movement;
						CurrentCommand.LoopCommands.Add(CurrentLoopCommand);
						i += 2;
						CurrentLoopOperator = CommandsArray[i].ToLower();
					}
					if (CurrentLoopOperator == "end")
					{
						CurrentCommand.LoopIterator = 0;
						CompiledProgram.Add(CurrentCommand);
						i += 1;
					}
						
				}
			}
		}
		for (int32 i = 0; i < CompiledProgram.Num(); i++)
		{
			UE_LOG(ProgramInputLog, Error, TEXT("Command №%i  %s   %i"), i+1, *CompiledProgram[i].Operation, CompiledProgram[i].Parametr);
		}
		UE_LOG(ProgramInputLog, Error, TEXT("Program has been compiled"));
		UE_LOG(ProgramInputLog, Error, TEXT("Number of Commands = %i"), CompiledProgram.Num());
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