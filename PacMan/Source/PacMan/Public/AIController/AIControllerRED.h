// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerRED.generated.h"

UCLASS()
class PACMAN_API AAIControllerRED : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIControllerRED();

	// === BEHAVIOR TREE ===
	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* TreeAsset;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	class UBlackboardComponent* MyBlackboard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	
};
