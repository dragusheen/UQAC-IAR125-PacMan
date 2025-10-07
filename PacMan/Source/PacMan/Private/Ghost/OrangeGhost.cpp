// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/OrangeGhost.h"
#include "Player/PacManPlayer.h"
#include "Kismet/GameplayStatics.h"

void AOrangeGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Pac = Cast<APacManPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APacManPlayer::StaticClass()));
	if (!Pac || bIsDead) return;

	float Dist = FVector::Dist(GetActorLocation(), Pac->GetActorLocation());
	if (Dist < 300.f)
	{
		FVector RandomOffset = FVector(FMath::RandRange(-400, 400), FMath::RandRange(-400, 400), 0);
		Seek(GetActorLocation() + RandomOffset, DeltaTime);
	}
	else
	{
		Seek(Pac->GetActorLocation(), DeltaTime);
	}
}


