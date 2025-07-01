#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DRPlayerState.generated.h"

/**
 * ADRPlayerState
 * A base player state for the SpaceGame.
 */
UCLASS()
class DEADRAIN_API ADRPlayerState : public APlayerState
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRPlayerState();

    protected:
        virtual void BeginPlay() override;

#pragma endregion


};