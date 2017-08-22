// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonMakerTopDownCharacter.generated.h"

UCLASS()
class DUNGEONMAKERALPHA_API ADungeonMakerTopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADungeonMakerTopDownCharacter();
	UPROPERTY(EditAnywhere)
	int selectedPiece = 1;
	UPROPERTY(EditAnywhere)
	int rotationNumber = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FHitResult Hit;

	class ABuildingBlock* buildingBlock;
	class ABuildingBlock* cachedBuildingBlock;

	bool bBuildingBlock = false;
	bool bCreating = true;

	//void displayChoices();


	//int previewedRotation;

	bool somethingChanged = false;

	int rowsToSelect = 1;
	int columnsToSelect = 1;

	void ProgressLeft();
	void ProgressRight();
	void RotateUp();
	void RotateDown();

	//void MoveForward(float Val);
	//void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	void OnFire();
	void OnDestroy();
	void OpenMenu();
	void Save();
	void Load();

	class ABuildHandler* theBuildHandler;

	void SetMousePosition(float LocatonX, float LocationY);

	APlayerController* theController;
};
