// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingBlock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Materials/Material.h"
#include "BuildHandler.h"
#include "MazePiece.h"

// Sets default values
ABuildingBlock::ABuildingBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	savePieceNumber = 0;
	saveRotNumber = 0;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->bGenerateOverlapEvents = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	//DefaultMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("DefaultMaterial"));

	//HighlightedMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("HighlightedMaterial"));
	//SelectedMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("SelectedMaterial"));

	//DefaultMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Default.Default"), NULL, LOAD_None, NULL);
	//HighlightedMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Highlighted.Highlighted"), NULL, LOAD_None, NULL);
	//SelectedMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Selected.Selected"), NULL, LOAD_None, NULL);

	DefaultMaterial = CreateDefaultSubobject<UMaterial>(TEXT("DefaultMaterial"));
	HighlightedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("HighlightedMaterial"));
	SelectedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("SelectedMaterial"));
	InvalidMaterial = CreateDefaultSubobject<UMaterial>(TEXT("InvalidMaterial"));


	selected = false;

	//Will Likely Delete
	//DISCLAIMER: TESTING
	Ends.Init(false, 4);
}

// Called when the game starts or when spawned
void ABuildingBlock::BeginPlay()
{
	Super::BeginPlay();
	SwitchMaterialToDefault();
}

// Called every frame
void ABuildingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBlock::SwitchMaterialToDefault(int columnsToSelect, int rowsToSelect)
{
	/*
	if (!selected) {
	Mesh->SetMaterial(0, DefaultMaterial);
	}
	else {
	Mesh->SetMaterial(0, TransparentMaterial);
	}
	*/
	for (int i = column; i < column + columnsToSelect; i++) {
		for (int j = row; j < row + rowsToSelect; j++) {
			if (theBuildHandler->BuildingBlockColumns.IsValidIndex(i) && theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows.IsValidIndex(j))
			{
				theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows[j]->SwitchMaterialToDefault();
			}
		}
	}
	if (piece && !selected) {
		piece->DestroyPieces();
		piece->Destroy(); savePieceNumber = 0;

		piece = NULL;
	}
	canPlace = true;
}
void ABuildingBlock::SwitchMaterialToDefault() {
	if (!selected) {
		Mesh->SetMaterial(0, DefaultMaterial);
	}
	else {
		Mesh->SetMaterial(0, TransparentMaterial);
	}
	//return true;
}
/*
void ABuildingBlock::SwitchMaterialToHighlighted(int columnsToSelect, int rowsToSelect, int pieceNum)
{
for (int i = column; i < column + columnsToSelect; i++) {
for (int j = row; j < row + rowsToSelect; j++) {
bool result = false;
if (theBuildHandler->BuildingBlockColumns.IsValidIndex(i) && theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows.IsValidIndex(j))
{
result = theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows[j]->SwitchMaterialToHighlighted();
}

if (result == false) {
canPlace = false;
}
}
}
if (canPlace) {
if (piece) {
piece->Destroy();
piece = NULL;
}
theBuildHandler->placePiece(pieceNum, this, GetWorld());
}
}
*/
void ABuildingBlock::SwitchMaterialToHighlighted(int columnsToSelect, int rowsToSelect, int pieceNum, int rotationNum)
{
	for (int i = column; i < column + columnsToSelect; i++) {
		for (int j = row; j < row + rowsToSelect; j++) {
			bool result = false;
			if (theBuildHandler->BuildingBlockColumns.IsValidIndex(i) && theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows.IsValidIndex(j))
			{
				result = theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows[j]->SwitchMaterialToHighlighted();
			}

			if (result == false) {
				canPlace = false;
			}
		}
	}
	if (canPlace) {
		if (piece) {
			piece->DestroyPieces();
			piece->Destroy(); 
			//piece->~AMazePiece();
			//piece->Destroy(); 

			piece = NULL;
		}
		theBuildHandler->placePiece(pieceNum, rotationNum, this);

	}
	/*
	if (!selected) {
	Mesh->SetMaterial(0, HighlightedMaterial);
	}
	else {
	Mesh->SetMaterial(0, InvalidMaterial);
	}
	*/
}
bool ABuildingBlock::SwitchMaterialToHighlighted() {
	if (!selected) {
		//Mesh->SetMaterial(0, HighlightedMaterial);
		Mesh->SetMaterial(0, HighlightedMaterial);
		return true;
	}
	else {
		Mesh->SetMaterial(0, InvalidMaterial);
		return false;
	}
}
void ABuildingBlock::DeletePiece(int columnsToSelect, int rowsToSelect)
{
	for (int i = column; i < column + columnsToSelect; i++) {
		for (int j = row; j < row + rowsToSelect; j++) {
			bool result = false;
			if (theBuildHandler->BuildingBlockColumns.IsValidIndex(i) && theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows.IsValidIndex(j))
			{
				theBuildHandler->BuildingBlockColumns[i]->BuildingBlockRows[j]->DeletePiece();
			}
		}
	}
}
void ABuildingBlock::DeletePiece() {
	if (selected && piece) {
		//theBuildHandler->
		piece->DestroyPieces();
		piece->Destroy(); 
		savePieceNumber = 0;
		saveRotNumber = 0;
		piece = NULL;
		selected = false;
		canPlace = true;
	}
}
/*
void ABuildingBlock::SwitchMaterialToSelected(int columnsToSelect, int rowsToSelect, int pieceNum)
{

//Mesh->SetMaterial(0, SelectedMaterial);
//if (BlockSpawner) {
//BlockSpawner->placePiece(1, GetActorLocation());
//((AInstantiateBlocks*)BlockSpawner)->
//AInstantiateBlocks* Testing = Cast<AInstantiateBlocks>(BlockSpawner);
//if (Testing) {
if (!selected && canPlace) {
if (theBuildHandler) {
if (piece) {
piece->Destroy();
piece = NULL;
}
theBuildHandler->placePiece(pieceNum, this, GetWorld());
//Mesh->ToggleVisibility();
//Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//Mesh->SetWorldScale3D(FVector(0.f));
Mesh->SetMaterial(0, TransparentMaterial);
selected = true;
}
}
//}
//else {
//	UE_LOG(LogTemp, Warning, TEXT("Cast Failed"));
//}
//}
}
*/
void ABuildingBlock::SwitchMaterialToSelected(int columnsToSelect, int rowsToSelect, int pieceNum, int rotationNum)
{

	//Mesh->SetMaterial(0, SelectedMaterial);
	//if (BlockSpawner) {
	//BlockSpawner->placePiece(1, GetActorLocation());
	//((AInstantiateBlocks*)BlockSpawner)->
	//AInstantiateBlocks* Testing = Cast<AInstantiateBlocks>(BlockSpawner);
	//if (Testing) {
	if (!selected && canPlace) {
		if (theBuildHandler) {
			if (piece) {
				piece->DestroyPieces();
				piece->Destroy(); 
				piece = NULL;
			}
			Ends = theBuildHandler->placePiece(pieceNum, rotationNum, this);
			//Mesh->ToggleVisibility();
			//Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//Mesh->SetWorldScale3D(FVector(0.f));
			Mesh->SetMaterial(0, TransparentMaterial);
			selected = true;
			savePieceNumber = pieceNum;
			saveRotNumber = rotationNum;
		}
	}
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Cast Failed"));
	//}
	//}
}


USceneComponent* ABuildingBlock::getRootComponent() {
	//UStaticMeshComponent* Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	//return Mesh2;
	return RootComponent;
}