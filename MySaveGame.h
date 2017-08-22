// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"


USTRUCT()
struct FDungeon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		int columns;
	UPROPERTY()
		int rows;
	UPROPERTY()
		TArray<int> pieceNums;
	UPROPERTY()
		TArray<int> rotNums;

	FDungeon()
	{

	}
};
/**
 * 
 */
UCLASS()
class DUNGEONMAKERALPHA_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FDungeon FirstDungeon;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UMySaveGame();
	
};
