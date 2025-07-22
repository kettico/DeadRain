// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DRGameMode.generated.h"

class ADRBaseCharacter;


UCLASS()
class DEADRAIN_API ADRGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADRGameMode();

	UFUNCTION()
	void HandleCharacterDeath(ADRBaseCharacter* DeadCharacter);
};
