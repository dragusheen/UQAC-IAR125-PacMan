// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/Ghost.h"


AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Body"));
	RootComponent = Body;

	Collision = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
}

void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == EGhostState::Chase || CurrentState == EGhostState::Scatter)
	{
		//MoveGhost(DeltaTime);
	}
}

void AGhost::Seek(const FVector& Target, float DeltaTime)
{
	FVector DesiredVelocity = (Target - GetActorLocation()).GetSafeNormal() * MaxSpeed;
	FVector Steering = DesiredVelocity - Velocity;
	float Smoothness = 5.f;

	Velocity = FMath::VInterpTo(Velocity, Velocity + Steering, DeltaTime, Smoothness);
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	SetActorLocation(NewLocation);

	if (!Velocity.IsNearlyZero())
	{
		FRotator NewRotation = Velocity.Rotation();
		SetActorRotation(NewRotation);
	}
}

void AGhost::SetGhostState(EGhostState NewState)
{
	CurrentState = NewState;
}

void AGhost::OnEaten()
{
	SetGhostState(EGhostState::Dead);
	// Retourner au centre
}

void AGhost::OnFrightened()
{
	SetGhostState(EGhostState::Frightened);
}

void AGhost::ResetGhost()
{
	// Replace le fantôme au centre
}
