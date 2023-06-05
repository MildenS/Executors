// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExProgramInputWidget.generated.h"

class AExecutor;
class UButton;
class UMultiLineEditableText;
class AExGameModeBase;
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
	UPROPERTY(meta = (BindWidget))
	UButton* CompileButton;
	UPROPERTY(meta = (BindWidget))
	UMultiLineEditableText* ProgramInputField;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void CompileProgram();

private:
	//UPROPERTY()
	//TArray<FCommand> CompiledProgram;
	AExecutor* FindExecutor();
	AExGameModeBase* GetGameMode();
	void LogAllowedCommands(TArray<FCommand>& AllowedCommands);
};
