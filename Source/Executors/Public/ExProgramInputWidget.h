// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExProgramInputWidget.generated.h"

class AExecutor;
class UButton;
class SMultiLineEditableText;
struct FCommand;


/**
 * 
 */
UCLASS()
class EXECUTORS_API UExProgramInputWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	UButton* CompileButton;
	SMultiLineEditableText* ProgramInputField;
	virtual void NativeConstruct() override;
	void CompileProgram();

private:
	//UPROPERTY()
	//TArray<FCommand> CompiledProgram;
	AExecutor* FindExecutor();
};
