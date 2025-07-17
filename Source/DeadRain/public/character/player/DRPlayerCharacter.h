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

        virtual void PossessedBy(AController* NewController) override;

    protected:
        virtual void BeginPlay() override;
        virtual void OnRep_PlayerState() override;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        UCameraComponent* Camera;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        USpringArmComponent* SpringArm;

#pragma endregion

#pragma region INTERACTION
    public:
        UFUNCTION(BlueprintCallable, Category = "Interaction")
        ADRInteractableActor* GetCurrentInteractable() const { return CurrentInteractable; }
    protected:
        UFUNCTION(BlueprintCallable, Category = "Interaction")
        void TickInteractionCheck();

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        ADRInteractableActor* CurrentInteractable = nullptr;    
        
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        float InteractionDistance = 200.0f; // Distance to check for interactable actors




        
    
#pragma endregion


#pragma region GAS
public:
    virtual void Die() override;
protected:
    virtual void InitializeGAS() override;
    #pragma region ATTRIBUTES
        virtual void CurrentHealthChanged(const FOnAttributeChangeData& Data) override ;
        virtual void MaxHealthChanged(const FOnAttributeChangeData& Data) override ;
        virtual void HealthRegenChanged(const FOnAttributeChangeData& Data) override ;

        virtual void CurrentStaminaChanged(const FOnAttributeChangeData& Data) override ;
        virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data) override ;
        virtual void StaminaRegenChanged(const FOnAttributeChangeData& Data) override ;

        virtual void CurrentManaChanged(const FOnAttributeChangeData& Data) override ;
        virtual void MaxManaChanged(const FOnAttributeChangeData& Data) override ;
        virtual void ManaRegenChanged(const FOnAttributeChangeData& Data) override ;

    #pragma endregion

#pragma endregion

};