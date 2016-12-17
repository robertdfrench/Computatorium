// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "WorkerMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMPUTATORIUM_API UWorkerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
