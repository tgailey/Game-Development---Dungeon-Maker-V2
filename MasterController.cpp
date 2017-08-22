// Fill out your copyright notice in the Description page of Project Settings.
#include "MasterController.h"
#include "DungeonMakerAlpha.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "GlobalInstance.h"
#include "DungeonMakerAlphaCharacter.h"
#include "DungeonMakerTopDownCharacter.h"
#include "Engine/World.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"

AMasterController::AMasterController()
	:
	APlayerController()
{


	InputYawScale = 2.5f;
	InputPitchScale = -1.75f;
	InputRollScale = 1.f;

	//FirstPersonCharacter = ADungeonMakerAlphaCharacter::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/MyGenericTownCharacter"));
	TownCharacter = PlayerPawnClassFinder.Class;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder1(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	FirstPersonCharacter = PlayerPawnClassFinder1.Class;
	TopDownCharacter = ADungeonMakerTopDownCharacter::StaticClass();

	/*
	if (FirstPersonCharacter) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "FirstPersonCharacter - true");
	}
	if (!World) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "World - false");

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "World - true");

	}
	*/
}

void AMasterController::BeginPlay()
{
	Super::BeginPlay();
	if (((UGlobalInstance*)UGameplayStatics::GetGameInstance(this))->gameState == 0) {
		bAutoManageActiveCameraTarget = true;
		FActorSpawnParameters SpawnInfo;
		FVector Location = FVector(0.f, 0.f, 300.f);
		CreatedCharacter = GetWorld()->SpawnActor<ACharacter>(TownCharacter, Location, FRotator::ZeroRotator, SpawnInfo);
		Possess(CreatedCharacter);
	}
	else if (((UGlobalInstance*)UGameplayStatics::GetGameInstance(this))->gameState == 1) {
		
		bAutoManageActiveCameraTarget = true;
		FActorSpawnParameters SpawnInfo;
		FVector Location = FVector(0.f, 0.f,150.f);
		CreatedCharacter = GetWorld()->SpawnActor<ACharacter>(FirstPersonCharacter, Location, FRotator::ZeroRotator, SpawnInfo);
		Possess(CreatedCharacter);

	}
	else if (((UGlobalInstance*)UGameplayStatics::GetGameInstance(this))->gameState == 2) {
		
		bAutoManageActiveCameraTarget = false;
		FActorSpawnParameters SpawnInfo;
		FVector SpawnLocation = FVector(0.f, 0.f, 150.f);
		FVector Location = FVector(0.f, 0.f, 22000.0f);
		FRotator Rotation = FRotator(270.f, 0.f, 0.f);
		CreatedCharacter = GetWorld()->SpawnActor<ACharacter>(TopDownCharacter, SpawnLocation, FRotator::ZeroRotator, SpawnInfo);
		CreatedCharacter->SetupPlayerInputComponent(InputComponent);
		//Possess(CreatedCharacter);

		theCamera = GetWorld()->SpawnActor<ACameraActor>(Location, Rotation, SpawnInfo);
	//	theCamera->SetActorRotation(Rotation);
		SetViewTarget(theCamera);
		bShowMouseCursor = true;

	}

}


