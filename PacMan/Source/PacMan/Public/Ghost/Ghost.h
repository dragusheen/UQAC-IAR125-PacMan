// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Ghost.generated.h"


UCLASS()
class PACMAN_API AGhost : public ACharacter
{
	GENERATED_BODY()

public:
	AGhost();

protected:
	virtual void BeginPlay() override;

	// === COMPONENTS ===
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* FlipbookComponent;

	// === MOVEMENT ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghost|Settings")
	float MaxSpeed = 200.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ghost|Movement")
	FVector Velocity;

	// === STATE ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghost|AI")
	bool bIsFrightened = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghost|AI")
	bool bIsDead = false;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void Seek(const FVector& Target, float DeltaTime);
	virtual void Die();
	virtual void SetFrightenedMode(bool bActive);
	virtual void ResetToHome(const FVector& HomeLocation);

protected:
	FVector HomeLocation;
};
