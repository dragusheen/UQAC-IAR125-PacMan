// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ghost.h"
#include "RedGhost.generated.h"
                                                                                                    
UCLASS()
class PACMAN_API ARedGhost : public AGhost
{
	GENERATED_BODY()

	// === BEHAVIOR TREE ===
	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;
	
};
