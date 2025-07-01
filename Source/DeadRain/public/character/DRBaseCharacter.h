#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DRBaseCharacter.generated.h"

class UDRItemManager;
class ADRItem;
class ADRWeapon;
UCLASS()
class DEADRAIN_API ADRBaseCharacter : public ACharacter
{
    GENERATED_BODY()


#pragma region CORE
    public:
        ADRBaseCharacter();
        virtual void Tick(float DeltaTime) override;
    protected:
        virtual void BeginPlay() override;
#pragma endregion

#pragma region INVENTORY
    public:
    protected:
#pragma endregion    

#pragma region WEAPON
    public:
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void EquipWeapon(ADRWeapon* NewWeapon);
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void UnEquipWeapon();

        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void ActivateWeaponPrimary();
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void ActivateWeaponSecondary();
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void ActivateWeaponTertiary();

        void ApplyDamageToTarget(AActor* Target);
        void ReveiveDamage(float DamageAmount, AActor* DamageCauser);
        
    protected:
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        ADRWeapon* CurrentWeapon;
#pragma endregion

#pragma region STATS
    public:
        
    protected:
        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "STATS")
        float MaxHealth = 100.f;
        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "STATS")
        float CurrentHealth = 100.f;


#pragma endregion
    
};