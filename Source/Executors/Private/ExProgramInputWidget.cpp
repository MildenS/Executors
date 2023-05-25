// Fill out your copyright notice in the Description page of Project Settings.


#include "ExProgramInputWidget.h"
#include "Components/Button.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "ExCoreTypes.h"
#include "Executors/Executor.h"

void UExProgramInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CompileButton->OnClicked.AddDynamic(this, &UExProgramInputWidget::CompileProgram);
}

void UExProgramInputWidget::CompileProgram()
{
	TArray<FCommand> CompiledProgram;
	CompiledProgram.Empty();
	FString Program = ProgramInputField->GetText().ToString();
	TArray<FString> CommandsArray;
	TUniquePtr<TCHAR[]> DelimsArray(new TCHAR[2]);
	DelimsArray[0] = TCHAR(' ');
	DelimsArray[1] = TCHAR(',');
	if (!Program.IsEmpty())
	{
		int32 CommandsNum = Program.ParseIntoArray(CommandsArray, DelimsArray.Get(), true);
		if (CommandsNum > 1)
		{
			int32 i = 0;
			while (i < CommandsArray.Num())
			{
				FString CurrentOperator = CommandsArray[i].ToLower();
				int32 CurrentParametr = FCString::Atoi(*CommandsArray[i + 1]);
				FCommand CurrentCommand(CurrentOperator, CurrentParametr);
				CompiledProgram.Add(CurrentCommand);
			}
		}
		//закомменченоЮ пока не создам класс Исполнитля
		UPROPERTY()
			AExecutor* Executor = FindExecutor();
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
			break;
		}
	}
	return Executor;
}