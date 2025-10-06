// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Ghost.generated.h"

UENUM(BlueprintType)
enum class EGhostState : uint8
{
	Chase,      // Mode poursuite
	Scatter,    // Mode dispersion
	Frightened, // Mode effrayé (bleu)
	Dead        // Fantôme mangé, retourne au centre
};

UCLASS()
class PACMAN_API AGhost : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghost|Movement")
	float MaxSpeed = 200.f;

	FVector Velocity;
	EGhostState CurrentState;

	FVector ScatterTarget; // Coin de la carte pour mode scatter

public:
	AGhost();

	virtual void Tick(float DeltaTime) override;

	virtual void Seek(const FVector& Target, float DeltaTime);

	//virtual void MoveGhost(float DeltaTime); // Surchargée dans les classes enfants

	virtual void SetGhostState(EGhostState NewState);
	virtual void OnEaten(); // Quand le fantôme est mangé
	virtual void OnFrightened(); // Mode effrayé
	virtual void ResetGhost(); // Retour au centre
};