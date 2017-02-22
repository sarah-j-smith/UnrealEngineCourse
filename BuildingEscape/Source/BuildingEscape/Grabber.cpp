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

    SetUpPhysicsHandle();
    SetUpInputComponent();

    if (PhysicsHandle && InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Grabber good to go"));
    }
}

void UGrabber::SetUpPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Grabber requires %s must have PhysicsHandle attached."), *GetOwner()->GetName());
    }
}

void UGrabber::SetUpInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Grabber requires %s must have InputComponent attached."), *GetOwner()->GetName());
    }
    else
    {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    RenderDebugLine();
    
    if (PhysicsHandle->GrabbedComponent != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Moving grabbed object"));
        PhysicsHandle->SetTargetLocation(FindReachVector());
    }
}

FVector UGrabber::FindReachVector() const
{
    FRotator PlayerRotation = FindPlayerRotation();
    FVector ReachVector = FindPlayerLocation() + PlayerRotation.Vector() * ReachDistance;
    return ReachVector;
}

FVector UGrabber::FindPlayerLocation() const
{
    FVector PlayerLocation;
    FRotator PlayerRotation;
    GetWorld()->GetFirstPlayerController()->AController::GetPlayerViewPoint(PlayerLocation, PlayerRotation);
    return PlayerLocation;
}

FRotator UGrabber::FindPlayerRotation() const
{
    FVector PlayerLocation;
    FRotator PlayerRotation;
    GetWorld()->GetFirstPlayerController()->AController::GetPlayerViewPoint(PlayerLocation, PlayerRotation);
    return PlayerRotation;
}

void UGrabber::RenderDebugLine() const
{
    DrawDebugLine(GetWorld(), FindPlayerLocation(), FindReachVector(), FColor::Red, false, 0, 0, 10.0f);
}

FHitResult UGrabber::GetHitResult() const
{
    FHitResult OutHitResult;
    FCollisionObjectQueryParams ObjectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
    FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(OUT OutHitResult, FindPlayerLocation(), FindReachVector(), ObjectQueryParams, QueryParams);
    return OutHitResult;
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grabber activated %s"), *GetOwner()->GetName());
    
    FHitResult OutHitResult = GetHitResult();
    AActor *Target = OutHitResult.GetActor();
    if (Target)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit object: %s"), *Target->GetName());
        GrabbedOjbect = Target;
        
        UPrimitiveComponent *ComponentToGrab = OutHitResult.GetComponent();
        if (ComponentToGrab != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Grabbed object: %s"), *Target->GetName());
            PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit object had no component"), *Target->GetName());
        }
    }
}

void UGrabber::Release()
{
    if (GrabbedOjbect != nullptr && GrabbedOjbect->GetName() != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s released"), *GrabbedOjbect->GetName());
        GrabbedOjbect = nullptr;
        if (PhysicsHandle->GrabbedComponent != nullptr)
        {
            PhysicsHandle->ReleaseComponent();
        }
    }
}

