#pragma once

#include "CoreMinimal.h"
#include "character/DRBaseCharacter.h"
#include "DREnemyCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ADRInteractableActor;
/**
 * ADRPlayerCharacter
 * A base player character for the SpaceGame.
 */
UCLASS()
class DEADRAIN_API ADREnemyCharacter : public ADRBaseCharacter
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADREnemyCharacter();
        virtual void Tick(float DeltaTime) override;

    protected:
        virtual void BeginPlay() override;


#pragma endregion

#pragma region INTERACTION
    public:

    protected:

        virtual void InitializeGAS() override;

#pragma endregion

};