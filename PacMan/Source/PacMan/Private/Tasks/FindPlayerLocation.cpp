// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get the navigation Area in the current level
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (NavArea)
	{
		// Get the current player position
		FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

		// Return true if found a random point in the navigation and around your player position
		if (NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), PlayerPosition, TargetLocation, 1.0f))
		{
			// Set value in the blackboard
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Target"), TargetLocation);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
