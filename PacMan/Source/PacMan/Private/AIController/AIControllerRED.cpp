// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/AIControllerRED.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AAIControllerRED::AAIControllerRED()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree component"));

	MyBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

// Called when the game starts or when spawned
void AAIControllerRED::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIControllerRED::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIControllerRED::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (TreeAsset && TreeAsset->BlackboardAsset)
	{
		RunBehaviorTree(TreeAsset);
		MyBlackboard->InitializeBlackboard(*TreeAsset->BlackboardAsset);
	}
}

