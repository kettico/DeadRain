#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

/**
 * ADRPlayerController
 * A basic player controller for the SpaceGame.
 */
UCLASS()
class DEADRAIN_API ADRPlayerController : public APlayerController
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRPlayerController();
        virtual void Tick(float DeltaTime) override;

    protected:
        virtual void BeginPlay() override;
        
#pragma endregion
};