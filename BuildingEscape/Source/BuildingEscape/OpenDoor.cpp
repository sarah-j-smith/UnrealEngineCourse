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
    Owner = GetOwner();
    FRotator rotation = Owner->GetActorRotation();
    ClosedAngle = rotation.Yaw;
}

void UOpenDoor::OpenDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
        LastOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if ((GetWorld()->GetTimeSeconds() - LastOpenTime) >= DoorCloseDelay)
    {
        CloseDoor();
    }
    
}

