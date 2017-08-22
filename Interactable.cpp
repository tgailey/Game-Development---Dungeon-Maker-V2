// Fill out your copyright notice in the Description page of Project Settings.
#include "Interactable.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GenericTownCharacter.h"
#include "Engine.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.SetTickFunctionEnable(false);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->bGenerateOverlapEvents = true;
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::PlayerCollision);
	Trigger->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::PlayerCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AGenericTownCharacter* GTC = Cast<AGenericTownCharacter>(OtherActor);
	if (GTC != NULL) {
		GTC->interactable = this;
	}
}
void AInteractable::DoAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Interaction Working");
}

