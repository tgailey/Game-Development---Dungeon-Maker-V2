// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MasterController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONMAKERALPHA_API AMasterController : public APlayerController
{
	GENERATED_BODY()

	AMasterController();
	public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACharacter> TownCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACharacter> FirstPersonCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACharacter> TopDownCharacter;
	UPROPERTY(EditAnywhere)
	ACharacter* CreatedCharacter;

	UPROPERTY(EditAnywhere)
		ACameraActor* theCamera;
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
