// This handles the building of every maze piece in game. At start of level, this creates all the building blocks from scratch based off save.

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

}

// Called when the game starts or when spawned
void ABuildHandler::BeginPlay()
{
	Super::BeginPlay();
	//Like many things, the code below is messy and unruly... will find better method later for naming and the like.

	//If the save exists, call the load level method
	if (UGameplayStatics::DoesSaveGameExist(TEXT("TestSaveSlot"), 0)) {
		LoadLevel();
	}
	else {
		//Otherwise, run through this double for loop and created a building block in every position, and place a fourway maze piece at center
		float YPos = 0.f - columns / 2 * 3200.0f;
		float XPos = 0.f + rows / 2 * 3200.0f;
		FActorSpawnParameters SpawnInfo;
		if (BB) {
			for (int i = 0; i < columns; i++)
			{
				BuildingBlockColumns.Add(new FBuildingBlockRows());
				for (int j = 0; j < rows; j++) {
					FVector WorldLocation = FVector(XPos, YPos, 145.f);
					//If Center, created a piece at that location
					if (j == rows / 2 && i == columns / 2)
					{
						BuildingBlockColumns[i]->BuildingBlockRows.Add(GetWorld()->SpawnActor<ABuildingBlock>(BB, WorldLocation, FRotator::ZeroRotator, SpawnInfo));
						BuildingBlockColumns[i]->BuildingBlockRows[j]->SetActorScale3D(FVector(42.5f));
						BuildingBlockColumns[i]->BuildingBlockRows[j]->theBuildHandler = this;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->column = i;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->row = j;
						BuildingBlockColumns[i]->BuildingBlockRows[j]->SwitchMaterialToSelected(1, 1, 1, 0);
					}
					//Else, just have the empty building block
					else {

						BuildingBlockColumns[i]->BuildingBlockRows.Add(GetWorld()->SpawnActor<ABuildingBlock>(BB, WorldLocation, FRotator::ZeroRotator, SpawnInfo));
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
		//Then save the level! Wooo!
		SaveLevel();
	}
}

// Called every frame
void ABuildHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//This method takes an array of ends that represent which ends are "open" for hallways, and which ones are "closed". It always has size 4,
//And is represented as true (open) or false (closed). East is index 0, south is index 1, west is index 2, and north is index 3
//Rotation Number is how many times the piece is being rotated.
//This is the most hard to understand method in the entire game thusfar, I need to do a better job of explaining/commenting.
TArray<bool> ABuildHandler::Recalculate(TArray<bool> end, int rotationNumber)
{
	//Temp array of ints to carry which ones are open and should not be blocked off. 
	TArray<int> valuedInts;

	//Go through entire end array, if a end is true (meaning the end is open) created an int (newAmount) that holds the new end that should be open based
	//off rotation. This is a bit confusing. If we have :- piece, with truth values true true false false, and we wanted to rotate it twice to -", with 
	//truth values false, false, true, true, we would need to move every value in the truth array up two places. However, if it passes the 3rd index (or north)
	//We would need to bring it back down to index 0 or east. That's what the code above does
	for (int i = 0; i < 4; i++) {
		if (end[i]) {
			int newAmount = i + rotationNumber;
			if (newAmount >= 4) {
				newAmount -= 4;
			}
			valuedInts.Add(newAmount);
		}
	}
	//This code takes the ints that represent the spots in the array we would need to be open and represents it as a bool of 4 values, which is what is needed.
	TArray<bool> ends;
	for (int i = 0; i < 4; i++)
	{
		if (valuedInts.Contains(i)) {
			ends.Add(true);
		}
		else {
			ends.Add(false);
		}
		//The below statement is for testing
		//UE_LOG(LogTemp, Warning, TEXT("Bool value is: %s"), ends[i] ? "true" : "false");

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


TArray<bool> ABuildHandler::placePiece(int pieceNumber, int rotationNumber, ABuildingBlock* Spawner)
{
	//Parameters explained
		//pieceNumber - all pieces have a pieceNumber, the first piece is piece one. Right now, there are only about 4 piece numbers
		//rotationNumber - how many times we have to rotate the piece
		//Spawner - The place at which the piece will be placed

	//Spawn Parameters, nothing special at this point
	FActorSpawnParameters SpawnInfo;

	//The MazePiece that is going to be spawned via this method.
	AMazePiece* SpawnedPiece;


	//These values represent whether there is a dead end at each side. East is index 0, south is index 1, west is index 2, and north is index 3
	TArray<bool> pieceValues;
	//Defaulted values into no dead ends.
	pieceValues.Init(true, 4);

	//Check if MazePiece that we want to place is valid
	if (MazePieces.IsValidIndex(pieceNumber - 1)) {
		//^^^***piece numbers start at 1, indexes start at 0. Every reference to MazePieces array will therefore be made to pieceNumber - 1***

		//Amount that we are going to rotate the object. For each value of rotationNumber, we will spin the MazePiece 90 degrees
		float RotationAmount = 90.f * rotationNumber;
		//A rotator with the value we just calculated to rotate
		FRotator NewRotation = FRotator(0.f, RotationAmount, 0.f);

		//Spawn the piece in the world at spawner location and calculated rotation
		SpawnedPiece = GetWorld()->SpawnActor<AMazePiece>(MazePieces[pieceNumber - 1], Spawner->GetActorLocation(), NewRotation, SpawnInfo);
		//Attach Component to Spawner in which it is built. This makes for fast removal and also keeps level hierachy making sense and looking clean
		SpawnedPiece->AttachToComponent(Spawner->getRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//Set the actor rotation to the rotation calculated. This was done because spawning it with the rotation was not working. May be irrelevant now.
		SpawnedPiece->SetActorRotation(NewRotation);
		//Set the piece variable of the block used to place this piece, to the piece that was created
		Spawner->piece = SpawnedPiece;

		//Calculates the end values
		//Set piece values equal to the default end values of the maze piece (for example, the straight hallway || has default values false, true, false, true
		pieceValues = SpawnedPiece->bEnds;
		//Calls method that takes rotation and calculates new values for ends. (for example, hallway rotated == will have changed values true, false, true, false based off the current rotation)
		pieceValues = Recalculate(pieceValues, rotationNumber);
		
		//Set the newly created maze piece variables for building block and build handler to their correct values.
		SpawnedPiece->theBuildHandler = this;
		SpawnedPiece->theBuildingBlock = Spawner;
	}

	//Return end values so it is known what ends to delete
	return pieceValues;
}
