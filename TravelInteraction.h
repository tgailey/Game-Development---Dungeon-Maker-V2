// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "TravelInteraction.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONMAKERALPHA_API ATravelInteraction : public AInteractable
{
	GENERATED_BODY()
public:
	ATravelInteraction();
	UFUNCTION()
	void DoAction() override;

	UPROPERTY(EditAnywhere)
	FName LevelName;
	UPROPERTY(EditAnywhere)
		int gameState;
};
