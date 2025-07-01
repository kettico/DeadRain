#pragma once

#include "CoreMinimal.h"
#include "character/DRBaseCharacter.h"
#include "DRPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ADRInteractableActor;
/**
 * ADRPlayerCharacter
 * A base player character for the SpaceGame.
 */
UCLASS()
class DEADRAIN_API ADRPlayerCharacter : public ADRBaseCharacter
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRPlayerCharacter();
        virtual void Tick(float DeltaTime) override;

    protected:
        virtual void BeginPlay() override;

#pragma endregion

#pragma region INTERACTION
    public:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        UCameraComponent* Camera;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        USpringArmComponent* SpringArm;

        UFUNCTION(BlueprintCallable, Category = "Interaction")
        ADRInteractableActor* GetCurrentInteractable() const { return CurrentInteractable; }
    protected:
        UFUNCTION(BlueprintCallable, Category = "Interaction")
        void TickInteractionCheck();

        UFUNCTION(BlueprintCallable, Category = "Interaction")
        void InputInteract();


        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        ADRInteractableActor* CurrentInteractable = nullptr;    
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        float InteractionDistance = 200.0f; // Distance to check for interactable actors

#pragma endregion

};