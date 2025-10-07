// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/RedGhost.h"
#include "Player/PacManPlayer.h"
#include "Kismet/GameplayStatics.h"


void ARedGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APacManPlayer* Pac = Cast<APacManPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APacManPlayer::StaticClass()));
	if (Pac && !bIsDead)
	{
		Seek(Pac->GetActorLocation(), DeltaTime);
	}
}


