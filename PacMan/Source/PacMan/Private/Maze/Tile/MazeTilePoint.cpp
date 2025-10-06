/*
Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

	(„• ֊ •„)❤  <  Have a good day !
	--U-----U------------------------
*/

/* ----- INCLUDES -----*/
#include "Maze/Tile/MazeTilePoint.h"


/* ----- PUBLIC -----*/
AMazeTilePoint::AMazeTilePoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(Root);
	FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionBox->InitBoxExtent(FVector(8.f, 8.f, 8.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionBox->SetupAttachment(Root);
}

void AMazeTilePoint::BeginPlay()
{
	Super::BeginPlay();

	if (!Flipbook) return;
	FlipbookComponent->SetFlipbook(Flipbook);
	FlipbookComponent->PlayFromStart();
	FlipbookComponent->SetLooping(true);
}

void AMazeTilePoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (Flipbook)
	{
		FlipbookComponent->SetFlipbook(Flipbook);
		FlipbookComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		FlipbookComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

		CollisionBox->SetBoxExtent(FVector(8.f, 8.f, 50.f));
		CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	}
	else
	{
		FlipbookComponent->SetFlipbook(nullptr);
		CollisionBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	}
}