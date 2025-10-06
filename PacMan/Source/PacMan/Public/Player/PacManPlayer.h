/*
Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

	(„• ֊ •„)❤  <  Have a good day !
	--U-----U------------------------
*/


/* ----- INCLUDES -----*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacManPlayer.generated.h"


/* ----- ENUM -----*/
UENUM(BlueprintType)
enum class EPacManDirection : uint8
{
	None,
	Up,
	Down,
	Left,
	Right
};


/* ----- CLASS -----*/
UCLASS()
class PACMAN_API APacManPlayer : public APawn
{
	GENERATED_BODY()

public:
	APacManPlayer();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MoveSpeed = 1.f;

private:
	FVector CurrentDirection;
	FVector NextDirection;
	EPacManDirection NextRotation;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	bool CanMove(FVector Direction);
	void UpdateFlipbookRotation();
};