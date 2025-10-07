// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/PinkGhost.h"
#include "Player/PacManPlayer.h"
#include "Kismet/GameplayStatics.h"

void APinkGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APacManPlayer* Pac = Cast<APacManPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APacManPlayer::StaticClass()));
	if (Pac && !bIsDead)
	{
		FVector Target = Pac->GetActorLocation() + Pac->GetActorForwardVector() * 200.f;
		Seek(Target, DeltaTime);
	}
}

