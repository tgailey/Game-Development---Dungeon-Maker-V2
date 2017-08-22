// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONMAKERALPHA_API UGlobalInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:

	UGlobalInstance(const FObjectInitializer& ObjectInitializer);

	/** Increment this value in any map, change map, and notice it persists! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DungeonMakerHUDCrosshair)
		int32 InterLevelPersistentValue;
	UPROPERTY(EditAnywhere)
	int gameState = 0;
	
	
};
