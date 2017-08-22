// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBlock.generated.h"

UCLASS()
class DUNGEONMAKERALPHA_API ABuildingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UMaterial* DefaultMaterial;
	UPROPERTY(EditAnywhere)
		UMaterial* HighlightedMaterial;
	UPROPERTY(EditAnywhere)
		UMaterial* SelectedMaterial;
	UPROPERTY(EditAnywhere)
		UMaterial* InvalidMaterial;
	UPROPERTY(EditAnywhere)
		UMaterial* TransparentMaterial;
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AInstantiateBlocks> BlockSpawner;

	class ABuildHandler* theBuildHandler;
	class AMazePiece* piece;

	UPROPERTY(EditAnywhere)
	int savePieceNumber = 0;
	UPROPERTY(EditAnywhere)
		int saveRotNumber = 0;

	UPROPERTY(EditAnywhere)
	int row;
	UPROPERTY(EditAnywhere)
	int column;
	bool canPlace = true;


	bool selected;
	UFUNCTION()
		void SwitchMaterialToDefault(int columnsToSelect, int rowsToSelect);

	void SwitchMaterialToDefault();

	//UFUNCTION()
//		void SwitchMaterialToHighlighted(int columnsToSelect, int rowsToSelect, int pieceNum);

	void SwitchMaterialToHighlighted(int columnsToSelect, int rowsToSelect, int pieceNum, int rotationNum);

	bool SwitchMaterialToHighlighted();

	void DeletePiece(int columnsToSelect, int rowsToSelect);
	void DeletePiece();
	//UFUNCTION()
		//void SwitchMaterialToSelected(int columnsToSelect, int rowsToSelect, int pieceNum);

	void SwitchMaterialToSelected(int columnsToSelect, int rowsToSelect, int pieceNum, int rotationNum);

	UPROPERTY(EditAnywhere)
	TArray<bool> Ends;

	UFUNCTION()
		USceneComponent* getRootComponent();
	
};
