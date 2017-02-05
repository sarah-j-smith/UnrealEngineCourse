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
    status = OpenableStatus::Closed;
    
    UE_LOG(LogTemp, Warning, TEXT("Captured closed angle %0.2f"), ClosedAngle);
}

void UOpenDoor::OpenDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
    status = OpenableStatus::Opened;
}

void UOpenDoor::CloseDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));
    status = OpenableStatus::Closed;
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if (PressurePlate->IsOverlappingActor(ActorThatOpens)) // && status == OpenableStatus::Closed)
    {
//        UE_LOG(LogTemp, Warning, TEXT("Opening door %s due to pressure plate %s"), *GetOwner()->GetName(), *PressurePlate->GetName());
        OpenDoor();
        LastOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if ((GetWorld()->GetTimeSeconds() - LastOpenTime) >= DoorCloseDelay) // && status == OpenableStatus::Opened)
    {
//        UE_LOG(LogTemp, Warning, TEXT("Closing door after %0.2f seconds"), DoorCloseDelay);
        CloseDoor();
    }
    
}

