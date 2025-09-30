/*
Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

		(„• ֊ •„)❤  <  Have a good day !
		--U-----U------------------------
*/


/* ----- INCLUDES -----*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "MazeTile.generated.h"


/* ----- CLASS -----*/
UCLASS()
class PACMAN_API AMazeTile : public AActor
{
	GENERATED_BODY()

public:
	AMazeTile();

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UBoxComponent* CollisionBox;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TMap<FString, UPaperSprite*> SpriteMap;

	virtual void OnConstruction(const FTransform& Transform) override;
	void SetNeighbor(const bool N, const bool S, const bool E, const bool O);

private:
	TMap<FString, FString> NeighborMap;
	void SetSprite(UPaperSprite* Sprite);
};
