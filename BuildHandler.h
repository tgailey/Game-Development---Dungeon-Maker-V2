// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildHandler.generated.h"


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

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABuildingBlock> BB;

	/*
	UPROPERTY(EditAnywhere)
	class ACustom_Try2Character* Character;
	*/
	/*
	// Old Way
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> FourWayMazePiece;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> CornerPiece;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> TwoWayHallwayPiece;
	*/
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class AMazePiece>> MazePieces;
	//TArray<TSubclassOf<class AActor>> MazePieces;
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class AActor>> RoomPieces;
	/*
	UPROPERTY(EditAnywhere)
	class ABuildingBlock* BB;
	*/
	UPROPERTY(EditAnywhere)
		int columns = 7;
	UPROPERTY(EditAnywhere)
		int rows = 7;
	//UFUNCTION()
	//void placePiece(int pieceNumber, class ABuildingBlock* Spawner, UWorld* World);
	//UFUNCTION()

	//Will Likely Change
	//DISCLAIMER: TESTING
	//Change Return Type To Void
	//void placePiece(int pieceNumber, int rotationNumber, class ABuildingBlock* Spawner, UWorld* World);
	TArray<bool> placePiece(int pieceNumber, int rotationNumber, class ABuildingBlock* Spawner, UWorld* World);
	//Will Likely Change
	//DISCLAIMER: TESTING
	TArray<bool> Recalculate(TArray<bool> end, int rotationNumber);
	//void Recalculate(TArray<bool>* end, int rotationNumber);


	TArray<FBuildingBlockRows*> BuildingBlockColumns;

	void LoadLevel();
	void SaveLevel();
};