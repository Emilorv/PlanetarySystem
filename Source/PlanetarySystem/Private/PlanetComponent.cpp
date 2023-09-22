// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetComponent.h"

// Sets default values for this component's properties
UPlanetComponent::UPlanetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Velocity = FVector(1.0f, 0.0f, 0.0f);
	InitialSpeed = 500.0f; 

	// ...
}


// Called when the game starts
void UPlanetComponent::BeginPlay()
{
	Super::BeginPlay();
	Velocity = InitialSpeed * Velocity.GetSafeNormal();

	// ...
	
}


// Called every frame
void UPlanetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector NewLocation = GetOwner()->GetActorLocation() + Velocity * DeltaTime;
	GetOwner()->SetActorLocation(NewLocation);

	// ...
}



FVector UPlanetComponent::GetVelocity() {
	return Velocity;
}

void UPlanetComponent::UpdateVelocity(FVector addVelocity) {
	Velocity += addVelocity;
}




