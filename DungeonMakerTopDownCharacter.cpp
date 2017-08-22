// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonMakerTopDownCharacter.h"
#include "Engine/World.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "BuildHandler.h"
#include "BuildingBlock.h"
#include "Engine.h"
#include "GlobalInstance.h"

// Sets default values
ADungeonMakerTopDownCharacter::ADungeonMakerTopDownCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADungeonMakerTopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	theController = UGameplayStatics::GetPlayerController(this, 0);
}

// Called every frame
void ADungeonMakerTopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//((APlayerController*)GetController())->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	
	theController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	
	buildingBlock = Cast<ABuildingBlock>(Hit.GetActor());
	//if ((buildingBlock && (!cachedBuildingBlock || cachedBuildingBlock != buildingBlock || (previewedPiece != selectedPiece || previewedRotation != rotationNumber))) && !bBuildingBlock)
	//if ((buildingBlock && (!cachedBuildingBlock || cachedBuildingBlock != buildingBlock || previewedPiece != selectedPiece)) && !bBuildingBlock)
	//if ((buildingBlock && (!cachedBuildingBlock || cachedBuildingBlock != buildingBlock || previewedPiece != selectedPiece)))
	if ((buildingBlock && (!cachedBuildingBlock || cachedBuildingBlock != buildingBlock || (somethingChanged))) && !bBuildingBlock)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Working");
		//SUPER IMPERFECT, WILL DO THIS BETTER SOON
		if (!theBuildHandler) {
			theBuildHandler = buildingBlock->theBuildHandler;
		}

		/*
		if (selectedPiece >= buildingBlock->theBuildHandler->MazePieces.Num) {
		selectedPiece = 0;
		}
		else if (selectedPiece < 0) {
		selectedPiece = buildingBlock->theBuildHandler->MazePieces.Num - 1;
		}
		*/

		//if (!(buildingBlock->selected)) {
		buildingBlock->SwitchMaterialToHighlighted(columnsToSelect, rowsToSelect, selectedPiece, rotationNumber);
		//buildingBlock->SwitchMaterialToHighlighted(numToSelect, selectedPiece);
		//}
		cachedBuildingBlock = buildingBlock;
		//previewedPiece = selectedPiece;
		//previewedRotation = rotationNumber;
		somethingChanged = false;
		bBuildingBlock = true;
	}
	else if ((!buildingBlock || cachedBuildingBlock != buildingBlock) && bBuildingBlock)
	{
		//if (!(cachedBuildingBlock->selected)) {
		cachedBuildingBlock->SwitchMaterialToDefault(columnsToSelect, rowsToSelect);
		//}
		bBuildingBlock = false;
	}
}

// Called to bind functionality to input
void ADungeonMakerTopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->ClearBindingValues();
	PlayerInputComponent->BindAction("ProgressRight", IE_Pressed, this, &ADungeonMakerTopDownCharacter::ProgressRight);
	PlayerInputComponent->BindAction("ProgressLeft", IE_Pressed, this, &ADungeonMakerTopDownCharacter::ProgressLeft);
	PlayerInputComponent->BindAction("RotateUp", IE_Pressed, this, &ADungeonMakerTopDownCharacter::RotateUp);
	PlayerInputComponent->BindAction("RotateDown", IE_Pressed, this, &ADungeonMakerTopDownCharacter::RotateDown);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADungeonMakerTopDownCharacter::OnFire);
	PlayerInputComponent->BindAction("AltFire", IE_Pressed, this, &ADungeonMakerTopDownCharacter::OnDestroy);

	PlayerInputComponent->BindAction("Save", IE_Pressed, this, &ADungeonMakerTopDownCharacter::Save);
	PlayerInputComponent->BindAction("Load", IE_Pressed, this, &ADungeonMakerTopDownCharacter::Load);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADungeonMakerTopDownCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADungeonMakerTopDownCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("OpenMenu", IE_Pressed, this, &ADungeonMakerTopDownCharacter::OpenMenu);
}

void ADungeonMakerTopDownCharacter::OpenMenu() {
	((UGlobalInstance*)UGameplayStatics::GetGameInstance(this))->gameState = 0;
	UGameplayStatics::OpenLevel(GetWorld(), "Town");
}
void ADungeonMakerTopDownCharacter::TurnAtRate(float Rate)
{
	if (Rate != 0.0f) {
		float LocationX;
		float LocationY;
		//(APlayerController*)ReceivePossessed(this)
		theController->GetMousePosition(LocationX, LocationY);
		//((APlayerController*)GetController())->GetMousePosition(LocationX, LocationY);
		LocationX += Rate * 7;
		SetMousePosition(LocationX, LocationY);
	}
}
void ADungeonMakerTopDownCharacter::LookUpAtRate(float Rate)
{
	if (Rate != 0.0f) {
		float LocationX;
		float LocationY;
		theController->GetMousePosition(LocationX, LocationY);
		//((APlayerController*)GetController())->GetMousePosition(LocationX, LocationY);
		LocationY += Rate * 7;
		SetMousePosition(LocationX, LocationY);
	}
}
void ADungeonMakerTopDownCharacter::SetMousePosition(float LocationX, float LocationY)
{
	FViewport* v = CastChecked<ULocalPlayer>(theController->Player)->ViewportClient->Viewport;
	//FViewport* v = CastChecked<ULocalPlayer>(((APlayerController*)GetController())->Player)->ViewportClient->Viewport;
	int intX = (int)LocationX;
	int intY = (int)LocationY;
	//((APlayerController*)GetController())->SetMouseLocation(intX, intY);
	theController->SetMouseLocation(intX, intY);
	//v->SetMouse(intX, intY);
}
void ADungeonMakerTopDownCharacter::OnFire()
{
	if (buildingBlock)
	{
		//displayChoices(buildingBlock);
		buildingBlock->SwitchMaterialToSelected(columnsToSelect, rowsToSelect, selectedPiece, rotationNumber);
		//buildingBlock->SwitchMaterialToSelected(numToSelect, selectedPiece);
	}
}
void ADungeonMakerTopDownCharacter::OnDestroy()
{
	if (buildingBlock)
	{
		if (buildingBlock->selected) {
			//displayChoices(buildingBlock);
			buildingBlock->DeletePiece(columnsToSelect, rowsToSelect);
			somethingChanged = true;
			bBuildingBlock = false;
			//buildingBlock->SwitchMaterialToSelected(numToSelect, selectedPiece);
		}
	}
}
void ADungeonMakerTopDownCharacter::Save()
{
	if (theBuildHandler)
	{
		theBuildHandler->SaveLevel();
	}
}
void ADungeonMakerTopDownCharacter::Load()
{
	if (theBuildHandler)
	{
		theBuildHandler->LoadLevel();
	}
}
void ADungeonMakerTopDownCharacter::ProgressLeft() {
	selectedPiece--;
	bBuildingBlock = false;
	somethingChanged = true;
	if (selectedPiece <= 0) {
		selectedPiece = 4;
	}
}
void ADungeonMakerTopDownCharacter::ProgressRight() {
	selectedPiece++;
	bBuildingBlock = false;
	somethingChanged = true;
	if (selectedPiece >= 5) {
		selectedPiece = 1;
	}
}
void ADungeonMakerTopDownCharacter::RotateUp() {
	rotationNumber++;
	bBuildingBlock = false;
	if (rotationNumber == 4) {
		rotationNumber = 0;
	}

	if (rowsToSelect != columnsToSelect) {
		if (buildingBlock) {
			buildingBlock->SwitchMaterialToDefault(columnsToSelect, rowsToSelect);
		}
		int tempSelect = rowsToSelect;
		rowsToSelect = columnsToSelect;
		columnsToSelect = tempSelect;
	}

	somethingChanged = true;
}
void ADungeonMakerTopDownCharacter::RotateDown() {
	rotationNumber--;
	bBuildingBlock = false;
	if (rotationNumber == -1) {
		rotationNumber = 3;
	}

	if (rowsToSelect != columnsToSelect) {
		if (buildingBlock) {
			buildingBlock->SwitchMaterialToDefault(columnsToSelect, rowsToSelect);
		}
		int tempSelect = rowsToSelect;
		rowsToSelect = columnsToSelect;
		columnsToSelect = tempSelect;
	}

	somethingChanged = true;
}