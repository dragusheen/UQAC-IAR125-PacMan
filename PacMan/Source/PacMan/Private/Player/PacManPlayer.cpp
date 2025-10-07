/*
Author:
        >> Nathan TIROLF - { ntirolf@etu.uqac.ca }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDES -----*/
#include "Player/PacManPlayer.h"


/* ----- PUBLIC -----*/
APacManPlayer::APacManPlayer()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(Root);
    CollisionBox->SetBoxExtent(FVector(8.f, 8.f, 8.f));
    CollisionBox->SetCollisionProfileName(TEXT("Pawn"));

    FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
    FlipbookComponent->SetupAttachment(Root);
    FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    MovementComponent->MaxSpeed = MoveSpeed;

    AutoPossessPlayer = EAutoReceiveInput::Player0;
    CurrentDirection = FVector::ZeroVector;
    NextDirection = FVector::ZeroVector;
}


/* ----- PROTECTED -----*/
void APacManPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!NextDirection.IsZero() && CanMove(NextDirection))
    {
        CurrentDirection = NextDirection;
        NextDirection = FVector::ZeroVector;
        UpdateFlipbookRotation();
    }

    if (!CurrentDirection.IsZero())
    {
        FVector NewLocation = GetActorLocation() + CurrentDirection * MoveSpeed * DeltaTime;
        if (CanMove(CurrentDirection))
        {
            SetActorLocation(NewLocation);
        }
        else
        {
            CurrentDirection = FVector::ZeroVector;
        }
    }
}

void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("MoveUp", EInputEvent::IE_Pressed, this, &APacManPlayer::MoveUp);
    PlayerInputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &APacManPlayer::MoveDown);
    PlayerInputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &APacManPlayer::MoveLeft);
    PlayerInputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &APacManPlayer::MoveRight);
}


/* ----- PRIVATE -----*/
void APacManPlayer::MoveUp()    { NextDirection = FVector(0, -1, 0); NextRotation = EPacManDirection::Up; }
void APacManPlayer::MoveDown()  { NextDirection = FVector(0, 1, 0); NextRotation = EPacManDirection::Down; }
void APacManPlayer::MoveLeft()  { NextDirection = FVector(-1, 0, 0); NextRotation = EPacManDirection::Left; }
void APacManPlayer::MoveRight() { NextDirection = FVector(1, 0, 0); NextRotation = EPacManDirection::Right; }

void APacManPlayer::UpdateFlipbookRotation() const
{
    FRotator NewRot = FRotator::ZeroRotator;
    switch (NextRotation)
    {
        case EPacManDirection::Up:
            NewRot = FRotator(0.f, -90.f, -90.f);
            break;
        case EPacManDirection::Down:
            NewRot = FRotator(0.f, 90.f, -90.f);
            break;
        case EPacManDirection::Left:
            NewRot = FRotator(180.f, 0.f, -90.f);
            break;
        case EPacManDirection::Right:
            NewRot = FRotator(0.f, 0.f, -90.f);
            break;
        default:
            break;
    }
    FlipbookComponent->SetWorldRotation(NewRot);
}

bool APacManPlayer::CanMove(const FVector Direction) const
{
    const FVector Start = GetActorLocation();
    const FVector End = Start + Direction * 16.f;
    FHitResult Hit;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    return !GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
}