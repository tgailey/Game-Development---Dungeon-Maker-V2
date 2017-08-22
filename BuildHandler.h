// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildHandler.generated.h"

//This struct allows for a 'cheat' for Unreal's lack of double arrays.
USTRUCT()
struct FBuildingBlockRows
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<class ABuildingBlock*> BuildingBlockRows;

	FBuildingBlockRows()
	{
	}
	void createArray(int size) {
	}
};


UCLASS()
class DUNGEONMAKERALPHA_API ABuildHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	//Default Building Block. Set outside in the editor
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABuildingBlock> BB;


	//An array holding all the MazePieces. Set outside in the Unreal editor
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class AMazePiece>> MazePieces;
	
	//Nothing here yet
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class AActor>> RoomPieces;

	//Amount of columns in the level, will be changeable later
	UPROPERTY(EditAnywhere)
		int columns = 7;

	//Amount of rows in the level, will be changeable later
	UPROPERTY(EditAnywhere)
		int rows = 7;

	//This method places a piece in the level
	TArray<bool> placePiece(int pieceNumber, int rotationNumber, class ABuildingBlock* Spawner);
	
	//This method calculates which ends are open and which ones are closed
	TArray<bool> Recalculate(TArray<bool> end, int rotationNumber);

	//Since Unreal does not allow for double arrays, I had to create an array of structs called FBuildingBlockRows which holds an array of building blocks
	TArray<FBuildingBlockRows*> BuildingBlockColumns;

	//Method to load the level's maze pieces
	void LoadLevel();
	//Method to save the level's maze pieces
	void SaveLevel();
};