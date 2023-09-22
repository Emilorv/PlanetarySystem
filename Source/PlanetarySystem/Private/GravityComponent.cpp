// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "PlanetComponent.h"

// Sets default values for this component's properties
UGravityComponent::UGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    GravityRadius = 10000.0f;
    GravityConstant = 1000.0f;
	// ...
}


// Called when the game starts
void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    ApplyGravity();
	// ...
}

void UGravityComponent::ApplyGravity()
{
    AActor* parent = GetOwner();
    UWorld* World = GetOwner()->GetWorld();
    if (!World)
    {
        // Handle the case where World is not valid.
        return;
    }

    // Get the center actor's location.
    FVector CenterLocation = GetOwner()->GetActorLocation();

    // Use the center location to apply gravitational force to all spheres within the specified radius.
    TArray<UStaticMeshComponent*> SphereComponents;
    for (TActorIterator<AActor> It(World); It; ++It)
    {
        AActor* Actor = *It;

        UStaticMeshComponent* MeshComponent = Actor->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComponent && MeshComponent->IsSimulatingPhysics())
        {
            // Check if the actor is within the specified radius.
            float Distance = FVector::Distance(CenterLocation, Actor->GetActorLocation());
            if (Distance <= GravityRadius && Distance >0.0f)
            {
                FVector ForceDirection = (CenterLocation - MeshComponent->GetComponentLocation()).GetSafeNormal();

                float Mass = GetOwner()->FindComponentByClass<UPrimitiveComponent>()->GetMass();
                float ForceMagnitude = GravityConstant* Mass / FMath::Max(1.0f, Distance * Distance);

                UPlanetComponent* PlanetComponent = Actor->FindComponentByClass<UPlanetComponent>();


                if (PlanetComponent) {
                    FVector VelocityChange = ForceDirection * ForceMagnitude * GetWorld()->DeltaTimeSeconds;
                    PlanetComponent->UpdateVelocity(VelocityChange);
                }
            }
        }
    }

}





