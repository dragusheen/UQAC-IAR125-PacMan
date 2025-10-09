// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/Ghost.h"

#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetupAttachment(Root);
	FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Root);
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
	//HomeLocation = GetActorLocation();
}

// void AGhost::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }

//void AGhost::Die()
//{
	//bIsDead = true;
	//SetActorHiddenInGame(true);
	//SetActorEnableCollision(false);
//}

//void AGhost::SetFrightenedMode(bool bActive)
//{
	//bIsFrightened = bActive;
	// On pourrait changer la couleur du sprite ici
//}

//void AGhost::ResetToHome(const FVector& InHomeLocation)
//{
	//bIsDead = false;
	//SetActorHiddenInGame(false);
	//SetActorEnableCollision(true);
	//SetActorLocation(InHomeLocation);
	//Velocity = FVector::ZeroVector;
//}


