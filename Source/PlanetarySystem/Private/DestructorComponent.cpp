// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructorComponent.h"

// Sets default values for this component's properties
UDestructorComponent::UDestructorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// Bind the OnHit function to the Hit event of the owning actor's root component
	if (AActor* Owner = GetOwner())
	{
		if (UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
		{
			UE_LOG(LogTemp, Log, TEXT("Loaded!"));

			RootComponent->OnComponentHit.AddDynamic(this, &UDestructorComponent::OnHit);
		}
	}
	// ...
}


// Called when the game starts
void UDestructorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDestructorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckForCollisions();

	// ...
}

// Function to handle collision with other actors
void UDestructorComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 32, FColor::Red, false, 5.0f);
	UE_LOG(LogTemp, Log, TEXT("Hit!"));

	// Check if the other actor is valid and not this actor itself
	if (OtherActor && OtherActor != GetOwner())
	{
		// Destroy the other actor on collision
		OtherActor->Destroy();
	}
}

void UDestructorComponent::CheckForCollisions()
{
	// Get the owning actor's location
	FVector StartLocation = GetOwner()->GetActorLocation();

	// Set the end location slightly below the owning actor's location (adjust this as needed)
	FVector EndLocation = StartLocation - FVector(0, 0, 10.0f);

	// Perform a line trace from the start to the end location
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner()); // Ignore collisions with the owner actor

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // Change this to the appropriate collision channel
		CollisionParams
	);

	// If a collision is detected, handle it
	if (bHit)
	{
		AActor* OtherActor = HitResult.GetActor();
		if (OtherActor)
		{
			// Handle the collision (e.g., destroy the other actor)
			OnHit(nullptr, OtherActor, nullptr, FVector::ZeroVector, HitResult);
		}
	}
}

