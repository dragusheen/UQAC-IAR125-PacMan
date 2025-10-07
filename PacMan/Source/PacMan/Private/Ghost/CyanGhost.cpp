// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/CyanGhost.h"
#include "Ghost/RedGhost.h"
#include "Player/PacManPlayer.h"
#include "Kismet/GameplayStatics.h"

void ACyanGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Pac = Cast<APacManPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APacManPlayer::StaticClass()));
	auto Red = Cast<ARedGhost>(UGameplayStatics::GetActorOfClass(GetWorld(), ARedGhost::StaticClass()));

	if (Pac && Red && !bIsDead)
	{
		FVector Dir = (Pac->GetActorLocation() - Red->GetActorLocation());
		FVector Target = Red->GetActorLocation() + Dir * 2.f;
		Seek(Target, DeltaTime);
	}
}


