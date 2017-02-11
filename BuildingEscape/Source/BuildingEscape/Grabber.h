// Copyright Smithsoft Pty Ltd 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    
    // Grab the object currently pointed at within reach.
    void Grab();
    
    // Release the currently grabbed object
    void Release();

private:
    UPROPERTY(EditAnywhere)
    float ReachDistance = 50.0;
    
    UPhysicsHandleComponent *PhysicsHandle = nullptr;
    
    UInputComponent *InputComponent = nullptr;
    
    AActor *GrabbedOjbect = nullptr;
};
