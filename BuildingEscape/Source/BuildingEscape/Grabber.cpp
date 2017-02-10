// Copyright Smithsoft Pty Ltd 2017

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("Grabber commencify"));
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    FVector PlayerLocation;
    FRotator PlayerRotation;
    GetWorld()->GetFirstPlayerController()->AController::GetPlayerViewPoint(PlayerLocation, PlayerRotation);
    
//    UE_LOG(LogTemp, Warning, TEXT("Rot: %s - Pos: (%0.2f, %0.2f)"), *PlayerRotation.ToString(), *PlayerLocation.ToString());
    
    FVector ReachVector = PlayerLocation + PlayerRotation.Vector() * ReachDistance;
    
//    DrawDebugLine(GetWorld(), PlayerLocation, ReachVector, FColor(255, 0, 0), false, 0, 0, 10.0f);
    FHitResult OutHitResult;
    FCollisionObjectQueryParams ObjectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
    FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(OUT OutHitResult, PlayerLocation, ReachVector, ObjectQueryParams, QueryParams);
    
    AActor *Target = OutHitResult.GetActor();
    if (Target)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit object: %s"), *Target->GetName());
    }
}

