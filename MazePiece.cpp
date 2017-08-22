// Fill out your copyright notice in the Description page of Project Settings.

#include "MazePiece.h"
#include "BuildingBlock.h"
#include "BuildHandler.h"
#include "Engine/World.h"

// Sets default values
AMazePiece::AMazePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bEnds.Init(true, 4);
}

// Called when the game starts or when spawned
void AMazePiece::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnInfo;
	//Spawn End pieces at every single end
	thePiece = GetWorld()->SpawnActor<AActor>(Piece, this->GetActorLocation(), this->GetActorRotation(), SpawnInfo);
	thePiece->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	theEnds.Add(GetWorld()->SpawnActor<AActor>(Ends[0], this->GetActorLocation(), this->GetActorRotation(), SpawnInfo));
	theEnds[0]->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	theEnds[0]->SetActorRotation(FRotator::ZeroRotator);
	theEnds.Add(GetWorld()->SpawnActor<AActor>(Ends[1], this->GetActorLocation(), this->GetActorRotation(), SpawnInfo));
	theEnds[1]->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	theEnds[1]->SetActorRotation(FRotator::ZeroRotator);
	theEnds.Add(GetWorld()->SpawnActor<AActor>(Ends[2], this->GetActorLocation(), this->GetActorRotation(), SpawnInfo));
	theEnds[2]->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	theEnds[2]->SetActorRotation(FRotator::ZeroRotator);
	theEnds.Add(GetWorld()->SpawnActor<AActor>(Ends[3], this->GetActorLocation(), this->GetActorRotation(), SpawnInfo));
	theEnds[3]->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	theEnds[3]->SetActorRotation(FRotator::ZeroRotator);

	//allow to check ends
	checkEnds = true;
}

void AMazePiece::DestroyPieces()
{
	thePiece->Destroy();
	for (int i = 0; i < theEnds.Num(); i++) {
		theEnds[i]->Destroy();
	}
	//theEnds.Empty();
}

// Called every frame
void AMazePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If check ends is true, call function check ends
	if (checkEnds) {
		if (theBuildHandler && theBuildingBlock) {
			CheckEnds();
			checkEnds = false;
		}
	}
}

//This code checks the ends and determines if the must be removed
void AMazePiece::CheckEnds()
{
	//UE_LOG(LogTemp, Warning, TEXT("CheckEndsCalled"));
	if (theBuildHandler && theBuildingBlock)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("have both components"));
		int row = theBuildingBlock->row;
		int column = theBuildingBlock->column;

		if (theBuildingBlock->Ends[0]) {
			//UE_LOG(LogTemp, Warning, TEXT("Ends0"));
			if (column < theBuildHandler->columns - 1 && theBuildHandler->BuildingBlockColumns[column + 1]->BuildingBlockRows[row]->piece) {
				if (theBuildHandler->BuildingBlockColumns[column + 1]->BuildingBlockRows[row]->Ends[2]) {
					AActor* End1;
					End1 = Cast<AActor>(theEnds[0]);
					if (End1) {
						End1->SetActorEnableCollision(false);
						End1->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting1"));
					}

					AActor* End2;
					End2 = Cast<AActor>(theBuildHandler->BuildingBlockColumns[column + 1]->BuildingBlockRows[row]->piece->theEnds[2]);
					if (End2) {
						End2->SetActorEnableCollision(false);
						End2->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting1"));
					}
					/*
					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column + 1]->BuildingBlockRows[row]->piece->Ends[2])->SetActorEnableCollision(false);
					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column + 1]->BuildingBlockRows[row]->piece->Ends[2])->SetActorHiddenInGame(true);
					UE_LOG(LogTemp, Warning, TEXT("Working"));
					*/
				}
			}
		}
		else {
			theEnds[0]->SetActorHiddenInGame(true);
		}
		if (theBuildingBlock->Ends[1]) {
			if (row < theBuildHandler->rows - 1 && theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row + 1]->piece) {
				if (theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row + 1]->Ends[3]) {
					AActor* End1;
					End1 = Cast<AActor>(theEnds[1]);
					if (End1) {
						End1->SetActorEnableCollision(false);
						End1->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting2"));
					}

					AActor* End2;
					End2 = Cast<AActor>(theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row + 1]->piece->theEnds[3]);
					if (End2) {
						End2->SetActorEnableCollision(false);
						End2->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting2"));
					}

					/*
					Cast<AActor>(Ends[1])->SetActorEnableCollision(false);
					Cast<AActor>(Ends[1])->SetActorHiddenInGame(true);

					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row - 1]->piece->Ends[3])->SetActorEnableCollision(false);
					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row - 1]->piece->Ends[3])->SetActorHiddenInGame(true);
					*/
				}
			}
		}
		else {
			theEnds[1]->SetActorHiddenInGame(true);
		}
		if (theBuildingBlock->Ends[2]) {
			if (column > 0 && theBuildHandler->BuildingBlockColumns[column - 1]->BuildingBlockRows[row]->piece) {
				if (theBuildHandler->BuildingBlockColumns[column - 1]->BuildingBlockRows[row]->Ends[0]) {
					UE_LOG(LogTemp, Warning, TEXT("whatthefuck"));


					AActor* End1;
					End1 = Cast<AActor>((theEnds[2]));
					if (End1) {
						End1->SetActorEnableCollision(false);
						End1->SetActorHiddenInGame(true);

						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting3"));
					}

					AActor* End2;
					End2 = Cast<AActor>(theBuildHandler->BuildingBlockColumns[column - 1]->BuildingBlockRows[row]->piece->theEnds[0]);
					if (End2) {
						End2->SetActorEnableCollision(false);
						End2->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting3"));
					}

					/*
					Cast<AActor>(Ends[2])->SetActorEnableCollision(false);
					Cast<AActor>(Ends[2])->SetActorHiddenInGame(true);

					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column - 1]->BuildingBlockRows[row]->piece->Ends[0])->SetActorEnableCollision(false);
					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column - 1]->BuildingBlockRows[row]->piece->Ends[0])->SetActorHiddenInGame(true);
					*/
				}
			}
		}
		else {
			theEnds[2]->SetActorHiddenInGame(true);
		}
		if (theBuildingBlock->Ends[3]) {
			if (row > 0 && theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row - 1]->piece) {
				if (theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row - 1]->Ends[1]) {
					AActor* End1;
					End1 = Cast<AActor>(theEnds[3]);
					if (End1) {
						End1->SetActorEnableCollision(false);
						End1->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting4"));
					}

					AActor* End2;
					End2 = Cast<AActor>(theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row - 1]->piece->theEnds[1]);
					if (End2) {
						End2->SetActorEnableCollision(false);
						End2->SetActorHiddenInGame(true);
						UE_LOG(LogTemp, Warning, TEXT("CAsting"));
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("NotCasting4"));
					}

					/*
					Cast<AActor>(Ends[3])->SetActorEnableCollision(false);
					Cast<AActor>(Ends[3])->SetActorHiddenInGame(true);

					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row + 1]->piece->Ends[1])->SetActorEnableCollision(false);
					Cast<AActor>(theBuildHandler->BuildingBlockColumns[column]->BuildingBlockRows[row + 1]->piece->Ends[1])->SetActorHiddenInGame(true);
					*/
				}
			}
		}
		else {
			theEnds[3]->SetActorHiddenInGame(true);
		}
	}
}