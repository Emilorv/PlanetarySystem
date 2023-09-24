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
			RootComponent->OnComponentBeginOverlap.AddDynamic(this, &UDestructorComponent::OnOverlapBegin);

		}
	}


	
}


// Called when the game starts
void UDestructorComponent::BeginPlay()
{
	Super::BeginPlay();


	// Create and attach the audio component
	ExplosionSoundComponent = NewObject<UAudioComponent>(this);
	ExplosionSoundComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	ExplosionSoundComponent->RegisterComponent();


	// Create and attach the particle component
	ExplosionParticleComponent = NewObject<UParticleSystemComponent>(this);
	ExplosionParticleComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	ExplosionParticleComponent->RegisterComponent();
	// ...
	// ...
	
}


// Called every frame
void UDestructorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Function to handle collision with other actors
void UDestructorComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is valid and not this actor itself
	UE_LOG(LogTemp, Log, TEXT("%s overlapped %s"), *OtherActor->GetActorLabel(), *GetOwner()->GetActorLabel());


	if (OtherActor && OtherActor != GetOwner() && OtherActor->GetActorLabel()!="Sun")
	{
		UE_LOG(LogTemp, Log, TEXT("%s crashed into %s"), *OtherActor->GetActorLabel(), *GetOwner()->GetActorLabel());

		// Play the sound
		if (ExplosionSoundComponent && ExplosionSound)
		{
			UE_LOG(LogTemp, Log, TEXT("Played a sound"));
			ExplosionSoundComponent->SetSound(ExplosionSound);
			ExplosionSoundComponent->Play();
		}

		// Play the particle effect
		if (ExplosionParticleComponent && ExplosionEffect)
		{
			ExplosionParticleComponent->SetTemplate(ExplosionEffect);
			ExplosionParticleComponent->Activate();

		}

		// Destroy the other actor on collision
		OtherActor->Destroy();
	}
}

