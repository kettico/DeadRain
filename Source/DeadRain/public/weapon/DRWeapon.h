#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interaction/DRInteractableActor.h"
#include "DRWeapon.generated.h"


class UStaticMeshComponent;


UCLASS()
class DEADRAIN_API ADRWeapon : public ADRInteractableActor
{
    GENERATED_BODY()

#pragma region CORE
public:    
    ADRWeapon();

    UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* WeaponMesh;
#pragma endregion

#pragma region INTERFACE
    public:

    protected:
#pragma endregion

        virtual void InteractPress_Implementation(ADRBaseCharacter* Interactor);
        virtual void InteractHold_Implementation(ADRBaseCharacter* Interactor);

#pragma region ATTACKS
public:
    UFUNCTION(BlueprintCallable)
    virtual void Primary();
    UFUNCTION(BlueprintCallable)
    virtual void Secondary();
    UFUNCTION(BlueprintCallable)
    virtual void Tertiary();
#pragma endregion
    
};