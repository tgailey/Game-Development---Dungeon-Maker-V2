// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazePiece.generated.h"

UCLASS()
class DUNGEONMAKERALPHA_API AMazePiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMazePiece();

	UFUNCTION()
		void DestroyPieces();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "MazePiece")
		TSubclassOf<class AActor> Piece;

	UPROPERTY()
		AActor* thePiece;
	UPROPERTY(EditDefaultsOnly, Category = "MazePiece")
		//TArray<TSubclassOf<class UBlueprint>> Ends;
		TArray<TSubclassOf<class AActor>> Ends;
	//TArray<class AActor*> Ends;

	UPROPERTY()
		TArray<AActor*> theEnds;
	//UPROPERTY(BlueprintReadable, Category = "MazePiece")
	class ABuildHandler* theBuildHandler;

	UFUNCTION()
		void CheckEnds();
	UPROPERTY(EditDefaultsOnly)
		TArray<bool> bEnds;
	//UPROPERTY(BlueprintReadable, Category = "MazePiece")
	class ABuildingBlock* theBuildingBlock;

	bool checkEnds = false;
};
