// Copyright Smithsoft Pty Ltd 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
    
	// Sets default values for this component's properties
	UOpenDoor();

    void OpenDoor();
    void CloseDoor();
    
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    UPROPERTY(EditAnywhere)
    float OpenAngle = -9.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume *PressurePlate;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 1.0f;
    
    UPROPERTY(EditAnywhere)
    float TriggerMassThreshold = 50.0f;
	
    float ClosedAngle = 0.0;
    
    AActor *Owner;
    double LastOpenTime = 0.0;
    
    float GetTotalMassOnPlate() const;
};

