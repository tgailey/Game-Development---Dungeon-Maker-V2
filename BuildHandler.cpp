// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildHandler.h"
#include "BuildingBlock.h"
#include "Engine/World.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "MazePiece.h"
// Sets default values
ABuildHandler::ABuildHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//BuildingBlockColumns.Init(CreateDefaultSubobject<FBuildingBlockRows>(TEXT("Column_")), columns);
	//BuildingBlockColumns.Init(NULL, columns);
	//BuildingBlockColumns.Init(NewObject())
	//BuildingBlockColumns.SetNum(columns);
	//for (int i = 0; i < columns; i++) {
	//BuildingBlockColumns[i]->BuildingBlockRows.Init(CreateDefaultSubobject<ABuildingBlock>(TEXT("Rows_")),rows);
	//BuildingBlockColumns[i]->BuildingBlockRows.Init(NULL, rows);
	//}

}

// Called when the game starts or when spawned
void ABuildHandler::BeginPlay()
{
	Super::BeginPlay();
	//Like many things, the code below is messy and unruly... will find better method later for naming and the like.
	if (UGameplayStatics::DoesSaveGameExist(TEXT("TestSaveSlot"), 0)) {
		LoadLevel();
	}
	else {
		float YPos = 0.f - columns / 2 * 3200.0f;
		float XPos = 0.f + rows / 2 * 3200.0f;
		FActorSpawnParameters SpawnInfo;
		if (BB) {
			for (int i = 0; i < columns; i++)
			{
				BuildingBlockColumns.Add(new FBuildingBlockRows());
				for (int j = 0; j < rows; j++) {
					FVector WorldLocation = FVector(XPos, YPos, 145.f);
					if (j == rows / 2 && i == columns / 2)
					{
						BuildingBlockColumns[i]->BuildingBlockRows.Add(GetWorld()->SpawnActor<ABuildingBlock>(BB, WorldLocation, FRotator::ZeroRotator, SpawnInfo));
						//UE_LOG(LogTemp, Warning, TEXT("BlockBuilt"));
						BuildingBlockColumns[i]->BuildingBlockRows[j]->SetActorScale3D(FVector(42.5f));
						BuildingBlockColumns[i]->BuildingBlockRows[j]->theBuildHandler = this;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->column = i;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->row = j;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->SwitchMaterialToSelected(1, 1, 1, 0);
						//UGameplayStatics::GetPlayerPawn(this, 0)->SetActorLocation(WorldLocation);
					}
					else {

						//BuildingBlockColumns[i]->BuildingBlockRows[j] = GetWorld()->SpawnActor<ABuildingBlock>(BB, WorldLocation, FRotator::ZeroRotator, SpawnInfo);
						BuildingBlockColumns[i]->BuildingBlockRows.Add(GetWorld()->SpawnActor<ABuildingBlock>(BB, WorldLocation, FRotator::ZeroRotator, SpawnInfo));
						//UE_LOG(LogTemp, Warning, TEXT("BlockBuilt"));
						BuildingBlockColumns[i]->BuildingBlockRows[j]->SetActorScale3D(FVector(42.5f));
						BuildingBlockColumns[i]->BuildingBlockRows[j]->theBuildHandler = this;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->column = i;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->row = j;
					}
					XPos -= 3200.0f;
				}
				YPos += 3200.0f;
				XPos = +rows / 2 * 3200.0f;
			}
		}
		SaveLevel();
	}
}

// Called every frame
void ABuildHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
void ABuildHandler::placePiece(int pieceNumber, ABuildingBlock* Spawner, UWorld* World)
{
FActorSpawnParameters SpawnInfo;
FRotator rotation = FRotator::ZeroRotator;
AActor* SpawnedPiece;
/* KEY FOR PIECES
1 - FourWayMazePieces
2 - Corner Piece / South East
3 - Corner Piece / South West
4 - Corner Piece / North West
5 - Corner Piece / North East

if (pieceNumber <= 1) {
//TSubclassOf<class AActor> WhatToSpawn = (UClass*)(LoadObject<UBlueprint>(NULL, TEXT("/Game/CreatedAssets/MazePieces/FourWayPiece/FbxScene_FourWayMazePiece.FbxScene_FourWayMazePiece"), NULL, LOAD_None, NULL)->GeneratedClass);
if (MazePieces.IsValidIndex(0)) {
SpawnedPiece = World->SpawnActor<AActor>(MazePieces[0], Spawner->GetActorLocation(), rotation, SpawnInfo);
//SpawnedPiece->AttachToActor(Spawner, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
Spawner->piece = SpawnedPiece;
SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

}
else if (pieceNumber < 6) {
//TSubclassOf<class AActor> WhatToSpawn = (UClass*)(LoadObject<UBlueprint>(NULL, TEXT("/Game/CreatedAssets/MazePieces/CornerPiece/FbxScene_CornerPiece.FbxScene_CornerPiece"), NULL, LOAD_None, NULL)->GeneratedClass);
int RotatorNumber = pieceNumber - 2;
float RotationAmount = 90.f * RotatorNumber;
FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

if (MazePieces.IsValidIndex(1)) {
SpawnedPiece = World->SpawnActor<AActor>(MazePieces[1], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
SpawnedPiece->SetActorRotation(NewRotation);
Spawner->piece = SpawnedPiece;
//Spawner->AttachToActor(SpawnedPiece, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//SpawnedPiece->SetupAttachment(Spawner->getRootComponent());
}
}
else {
UE_LOG(LogTemp, Warning, TEXT("Not Implemented Yet"));
}

}
*/

//Will Likely Change
//DISCLAIMER: TESTING
TArray<bool> ABuildHandler::Recalculate(TArray<bool> end, int rotationNumber)
{
	TArray<int> valuedInts;

	for (int i = 0; i < 4; i++) {
		if (end[i]) {
			int newAmount = i + rotationNumber;
			if (newAmount >= 4) {
				newAmount -= 4;
			}
			valuedInts.Add(newAmount);
		}
	}

	TArray<bool> ends;
	for (int i = 0; i < 4; i++)
	{
		if (valuedInts.Contains(i)) {
			ends.Add(true);
		}
		else {
			ends.Add(false);
		}
		UE_LOG(LogTemp, Warning, TEXT("Bool value is: %s"), ends[i] ? "true" : "false");

	}

	return ends;
}
void ABuildHandler::LoadLevel()
{

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++) {
			if (BuildingBlockColumns.IsValidIndex(i) && BuildingBlockColumns[i]->BuildingBlockRows.IsValidIndex(j)) {
				BuildingBlockColumns[i]->BuildingBlockRows[j]->DeletePiece();
				BuildingBlockColumns[i]->BuildingBlockRows[j]->Destroy();
			}
		}
		if (BuildingBlockColumns.IsValidIndex(i)) {
			BuildingBlockColumns[i]->BuildingBlockRows.Empty();
		}
	}
	BuildingBlockColumns.Empty();


	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	FDungeon theDungeon = LoadGameInstance->FirstDungeon;

	float YPos = 0.f - columns / 2 * 3200.0f;
	float XPos = 0.f + rows / 2 * 3200.0f;
	int iterator = 0;
	FActorSpawnParameters SpawnInfo;
	for (int i = 0; i < theDungeon.columns; i++)
	{
		BuildingBlockColumns.Add(new FBuildingBlockRows());
		for (int j = 0; j < theDungeon.rows; j++) {
			FVector WorldLocation = FVector(XPos, YPos, 145.f);

			BuildingBlockColumns[i]->BuildingBlockRows.Add(GetWorld()->SpawnActor<ABuildingBlock>(BB, WorldLocation, FRotator::ZeroRotator, SpawnInfo));
			//UE_LOG(LogTemp, Warning, TEXT("BlockBuilt"));
			BuildingBlockColumns[i]->BuildingBlockRows[j]->SetActorScale3D(FVector(42.5f));
			BuildingBlockColumns[i]->BuildingBlockRows[j]->theBuildHandler = this;
			BuildingBlockColumns[i]->BuildingBlockRows[j]->column = i;
			BuildingBlockColumns[i]->BuildingBlockRows[j]->row = j;
			if (theDungeon.pieceNums[iterator] > 0) {
				BuildingBlockColumns[i]->BuildingBlockRows[j]->SwitchMaterialToSelected(1, 1, theDungeon.pieceNums[iterator], theDungeon.rotNums[iterator]);
			}
			//UGameplayStatics::GetPlayerPawn(this, 0)->SetActorLocation(WorldLocation);
			XPos -= 3200.0f;
			iterator++;
		}
		YPos += 3200.0f;
		XPos = +rows / 2 * 3200.0f;
	}
}
void ABuildHandler::SaveLevel()
{
	FDungeon* theDungeon = new FDungeon();
	theDungeon->columns = columns;
	theDungeon->rows = rows;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++) {
			theDungeon->pieceNums.Add(BuildingBlockColumns[i]->BuildingBlockRows[j]->savePieceNumber);
			theDungeon->rotNums.Add(BuildingBlockColumns[i]->BuildingBlockRows[j]->saveRotNumber);
		}
	}
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->FirstDungeon = *theDungeon;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
//Will Likely Change
//DISCLAIMER: TESTING
//Change Return Type To Void
//void ABuildHandler::placePiece(int pieceNumber, int rotationNumber, ABuildingBlock* Spawner, UWorld* World)
TArray<bool> ABuildHandler::placePiece(int pieceNumber, int rotationNumber, ABuildingBlock* Spawner, UWorld* World)
{
	FActorSpawnParameters SpawnInfo;
	FRotator rotation = FRotator::ZeroRotator;
	//AActor* SpawnedPiece;
	AMazePiece* SpawnedPiece;
	/* KEY FOR PIECES
	1 - FourWayMazePieces
	2 - Corner Piece / South East
	3 - Corner Piece / South West
	4 - Corner Piece / North West
	5 - Corner Piece / North East
	*/

	//Will Likely Delete
	//DISCLAIMER: TESTING
	TArray<bool> pieceValues;
	pieceValues.Init(true, 4);

	int indexNumber = pieceNumber - 1;
	if (MazePieces.IsValidIndex(indexNumber)) {

		float RotationAmount = 90.f * rotationNumber;
		FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

		SpawnedPiece = World->SpawnActor<AMazePiece>(MazePieces[indexNumber], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
		SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpawnedPiece->SetActorRotation(NewRotation);
		Spawner->piece = SpawnedPiece;

		pieceValues = SpawnedPiece->bEnds;
		if (!pieceValues.IsValidIndex(0)) {
			pieceValues = { true, true, true, true };
		}
		pieceValues = Recalculate(pieceValues, rotationNumber);

		//Spawner->AttachToActor(SpawnedPiece, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//SpawnedPiece->SetupAttachment(Spawner->getRootComponent());

		SpawnedPiece->theBuildHandler = this;
		SpawnedPiece->theBuildingBlock = Spawner;
	}

	//pieceValues.Init(false, 4);
	/*
	if (pieceNumber <= 1) {
		//TSubclassOf<class AActor> WhatToSpawn = (UClass*)(LoadObject<UBlueprint>(NULL, TEXT("/Game/CreatedAssets/MazePieces/FourWayPiece/FbxScene_FourWayMazePiece.FbxScene_FourWayMazePiece"), NULL, LOAD_None, NULL)->GeneratedClass);

		//pieceValues = { true, true, true, true };
		if (MazePieces.IsValidIndex(0)) {

			//Get pieces default end values and then recalculate them based off the rotation
			pieceValues = Cast<AMazePiece>(MazePieces[0])->ends;
			if (!pieceValues.IsValidIndex(0)) {
				pieceValues = { true, true, true, true };
			}
			pieceValues = Recalculate(pieceValues, rotationNumber);
			float RotationAmount = 90.f * rotationNumber;
			FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

			SpawnedPiece = World->SpawnActor<AMazePiece>(MazePieces[0], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
			SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SpawnedPiece->SetActorRotation(NewRotation);
			Spawner->piece = SpawnedPiece;
			//Spawner->AttachToActor(SpawnedPiece, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//SpawnedPiece->SetupAttachment(Spawner->getRootComponent());

			SpawnedPiece->theBuildHandler = this;
			SpawnedPiece->theBuildingBlock = Spawner;
		}

	}
	else if (pieceNumber <= 2) {
		//TSubclassOf<class AActor> WhatToSpawn = (UClass*)(LoadObject<UBlueprint>(NULL, TEXT("/Game/CreatedAssets/MazePieces/CornerPiece/FbxScene_CornerPiece.FbxScene_CornerPiece"), NULL, LOAD_None, NULL)->GeneratedClass);

	//	pieceValues = { true, true, false, false };
	//	pieceValues = Recalculate(pieceValues, rotationNumber);

	//	float RotationAmount = 90.f * rotationNumber;
	//	FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

		if (MazePieces.IsValidIndex(1)) {

			//Get pieces default end values and then recalculate them based off the rotation
			pieceValues = Cast<AMazePiece>(MazePieces[1])->ends;
			if (!pieceValues.IsValidIndex(0)) {
				pieceValues = { true, true, true, true };
			}
			pieceValues = Recalculate(pieceValues, rotationNumber);
			float RotationAmount = 90.f * rotationNumber;
			FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

			SpawnedPiece = World->SpawnActor<AMazePiece>(MazePieces[1], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
			SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SpawnedPiece->SetActorRotation(NewRotation);
			Spawner->piece = SpawnedPiece;
			//Spawner->AttachToActor(SpawnedPiece, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//SpawnedPiece->SetupAttachment(Spawner->getRootComponent());

			SpawnedPiece->theBuildHandler = this;
			SpawnedPiece->theBuildingBlock = Spawner;

		}
	}
	else if (pieceNumber <= 3)
	{

		//pieceValues = { false, true, false, true };
		//pieceValues = Recalculate(pieceValues, rotationNumber);
		//pieceValues = Recalculate(pieceValues, rotationNumber);

		//float RotationAmount = 90.f * rotationNumber;

		//FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

		if (MazePieces.IsValidIndex(2)) {
			//Get pieces default end values and then recalculate them based off the rotation
			pieceValues = Cast<AMazePiece>(MazePieces[2])->ends;
			if (!pieceValues.IsValidIndex(0)) {
				pieceValues = { true, true, true, true };
			}
			pieceValues = Recalculate(pieceValues, rotationNumber);
			float RotationAmount = 90.f * rotationNumber;
			FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);


			SpawnedPiece = World->SpawnActor<AMazePiece>(MazePieces[2], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
			SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SpawnedPiece->SetActorRotation(NewRotation);
			Spawner->piece = SpawnedPiece;
			//Spawner->AttachToActor(SpawnedPiece, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//SpawnedPiece->SetupAttachment(Spawner->getRootComponent());

			SpawnedPiece->theBuildHandler = this;
			SpawnedPiece->theBuildingBlock = Spawner;
		}
	}
	else if (pieceNumber >= 4) {

		//pieceValues = { false, true, true, true };
		//pieceValues = Recalculate(pieceValues, rotationNumber);
		//pieceValues = Recalculate(pieceValues, rotationNumber);


		//float RotationAmount = 90.f * rotationNumber;

		//FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

		if (MazePieces.IsValidIndex(3)) {

			//Get pieces default end values and then recalculate them based off the rotation
			pieceValues = Cast<AMazePiece>(MazePieces[1])->ends;
			if (!pieceValues.IsValidIndex(0)) {
				pieceValues = { true, true, true, true };
			}
			pieceValues = Recalculate(pieceValues, rotationNumber);
			float RotationAmount = 90.f * rotationNumber;
			FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

			SpawnedPiece = World->SpawnActor<AMazePiece>(MazePieces[3], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
			SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SpawnedPiece->SetActorRotation(NewRotation);
			Spawner->piece = SpawnedPiece;
			//Spawner->AttachToActor(SpawnedPiece, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//SpawnedPiece->SetupAttachment(Spawner->getRootComponent());

			SpawnedPiece->theBuildHandler = this;
			SpawnedPiece->theBuildingBlock = Spawner;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Not Implemented Yet"));
		pieceValues = { false, false, false, false };
	}
	//BuildingBlockColumns[Spawner->column]->BuildingBlockRows[Spawner->row]->savePieceNumber = pieceNumber;
	//BuildingBlockColumns[Spawner->column]->BuildingBlockRows[Spawner->row]->saveRotNumber = rotationNumber;
//	BuildingBlockColumns[Spawner->column]->BuildingBlockRows[Spawner->row]->pieceNumber = pieceNumber;
	*/
	return pieceValues;
}
