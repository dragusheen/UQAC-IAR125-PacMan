/*
    Author:
		>> Nathan TIROLF - { ntirolf@etu.uqac.ca }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDES -----*/
#include "PacMan/Public/Maze/MazeTile.h"


/* ----- PUBLIC -----*/
AMazeTile::AMazeTile()
{
	PrimaryActorTick.bCanEverTick = false;

	SpriteMap.Empty();
	NeighborMap.Add("0000", "Solo");
	NeighborMap.Add("0001", "DeadEnd_O");
	NeighborMap.Add("0010", "DeadEnd_E");
	NeighborMap.Add("0100", "DeadEnd_S");
	NeighborMap.Add("1000", "DeadEnd_N");
	NeighborMap.Add("0011", "Straight_EO");
	NeighborMap.Add("1100", "Straight_NS");
	NeighborMap.Add("0101", "Corner_SO");
	NeighborMap.Add("0110", "Corner_ES");
	NeighborMap.Add("1001", "Corner_ON");
	NeighborMap.Add("1010", "Corner_NE");
	NeighborMap.Add("0111", "TJunction_ESO");
	NeighborMap.Add("1011", "TJunction_NEO");
	NeighborMap.Add("1101", "TJunction_NSO");
	NeighborMap.Add("1110", "TJunction_NSE");
	NeighborMap.Add("1111", "Cross");

	for (auto n : NeighborMap) SpriteMap.Add(n.Value, nullptr);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(Root);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(Root);
	CollisionBox->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionBox->SetGenerateOverlapEvents(false);

	CollisionBox->SetCanEverAffectNavigation(true);
}

void AMazeTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetSprite(DefaultSprite);
}

void AMazeTile::SetNeighbor(const bool N, const bool S, const bool E, const bool O)
{
	FString Result = "0000";
	Result[0] = N ? '1' : '0';
	Result[1] = S ? '1' : '0';
	Result[2] = E ? '1' : '0';
	Result[3] = O ? '1' : '0';

	UPaperSprite *Sprite = nullptr;
	if (DefaultSprite) Sprite = DefaultSprite;

	if (NeighborMap.Contains(Result))
	{
		FString Neighbor = NeighborMap[Result];
		Sprite = SpriteMap[Neighbor];
	}
	SetSprite(Sprite);
}


/* ----- PRIVATE -----*/
void AMazeTile::SetSprite(UPaperSprite* Sprite)
{
	if (Sprite)
	{
		SpriteComponent->SetSprite(Sprite);
		if (UPaperSprite* S = SpriteComponent->GetSprite())
		{
			const FVector2D Size = S->GetSourceSize();
			CollisionBox->SetBoxExtent(FVector(Size.X * 0.5, Size.Y * 0.5, 50.f));
			CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		}
	} else
	{
		SpriteComponent->SetSprite(nullptr);
		CollisionBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	}
}