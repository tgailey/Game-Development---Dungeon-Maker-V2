// Fill out your copyright notice in the Description page of Project Settings.

#include "TravelInteraction.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "GlobalInstance.h"
#include "Engine/World.h"


ATravelInteraction::ATravelInteraction() 
	:
	AInteractable()
{
	LevelName = TEXT("LevelOne");
	gameState = 2;
}

void ATravelInteraction::DoAction()
{
	((UGlobalInstance*)UGameplayStatics::GetGameInstance(this))->gameState = gameState;

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}