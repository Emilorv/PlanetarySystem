// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANETARYSYSTEM_API UGravityComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Gravity")
	float GravityRadius;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float GravityConstant;


public:	
	// Sets default values for this component's properties
	UGravityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ApplyGravity();

};
