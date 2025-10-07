// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/Ghost.h"

#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetupAttachment(Root);
	FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
	HomeLocation = GetActorLocation();
}

void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGhost::Seek(const FVector& Target, float DeltaTime)
{
	// Vecteur désiré (2D : Z = 0)
	FVector DesiredVelocity = (Target - GetActorLocation());
	DesiredVelocity.Z = 0;
	DesiredVelocity = DesiredVelocity.GetSafeNormal() * MaxSpeed;

	// Steering
	FVector Steering = DesiredVelocity - Velocity;

	// Lissage
	float Smoothness = 5.f;
	Velocity = FMath::VInterpTo(Velocity, Velocity + Steering, DeltaTime, Smoothness);

	// Mise à jour de la position
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	SetActorLocation(NewLocation, true); // true = respecte les collisions

	// Rotation du sprite
	if (!Velocity.IsNearlyZero())
	{
		FRotator NewRotation = Velocity.Rotation();
		SetActorRotation(NewRotation);
	}
}

void AGhost::Die()
{
	bIsDead = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AGhost::SetFrightenedMode(bool bActive)
{
	bIsFrightened = bActive;
	// On pourrait changer la couleur du sprite ici
}

void AGhost::ResetToHome(const FVector& InHomeLocation)
{
	bIsDead = false;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorLocation(InHomeLocation);
	Velocity = FVector::ZeroVector;
}


