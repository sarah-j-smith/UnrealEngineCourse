// Copyright Smithsoft Pty Ltd 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"

#include <iostream>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
    AActor *doorOwner = GetOwner();
    FRotator NewRotation = FRotator(0.0f, -40.0f, 0.0f);
    doorOwner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        UE_LOG(LogTemp, Warning, TEXT("Opening door %s due to pressure plate %s"), *GetOwner()->GetName(), *PressurePlate->GetName());
        OpenDoor();
    }
}

