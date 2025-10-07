// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ghost.h"
#include "CyanGhost.generated.h"

UCLASS()
class PACMAN_API ACyanGhost : public AGhost
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
};

