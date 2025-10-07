/*
Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

	(„• ֊ •„)❤  <  Have a good day !
	--U-----U------------------------
*/


/* ----- INCLUDES -----*/
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "MazeTilePoint.generated.h"


/* ----- CLASS -----*/
UCLASS()
class PACMAN_API AMazeTilePoint : public AActor
{
	GENERATED_BODY()

public:
	AMazeTilePoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* Root;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UPaperFlipbook* Flipbook;

	virtual void OnConstruction(const FTransform& Transform) override;
};
