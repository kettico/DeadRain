#include "character/DRBaseCharacter.h"
#include "weapon/DRWeapon.h"


#pragma region CORE
    ADRBaseCharacter::ADRBaseCharacter(){

    }

    void ADRBaseCharacter::Tick(float DeltaTime){
        Super::Tick(DeltaTime);
    }
    
    void ADRBaseCharacter::BeginPlay(){
        Super::BeginPlay();
    }
#pragma endregion

#pragma region WEAPON
    void ADRBaseCharacter::EquipWeapon(ADRWeapon* NewWeapon){
        if (!NewWeapon) return;

        if (CurrentWeapon) UnEquipWeapon();
        CurrentWeapon = NewWeapon;
    }

    void ADRBaseCharacter::UnEquipWeapon(){
        if (CurrentWeapon) return;
    }


    void ADRBaseCharacter::ActivateWeaponPrimary(){
        if (!CurrentWeapon) return;
        CurrentWeapon->Primary();
    }
    void ADRBaseCharacter::ActivateWeaponSecondary(){
        if (!CurrentWeapon) return;
        CurrentWeapon->Secondary();
    }
    void ADRBaseCharacter::ActivateWeaponTertiary(){
        if (!CurrentWeapon) return;
        CurrentWeapon->Tertiary();
    }


    void ADRBaseCharacter::ApplyDamageToTarget(AActor* Target){
        if (!Target) return;

        if (ADRBaseCharacter* TargetCharacter = Cast<ADRBaseCharacter>(Target)){
            float DamageAmount = 10.f; // Example damage amount
            TargetCharacter->ReveiveDamage(DamageAmount, this);
        }

    }

    void ADRBaseCharacter::ReveiveDamage(float DamageAmount, AActor* DamageCauser){
        if (DamageAmount <= 0) return;
        if (!DamageCauser) return;

        CurrentHealth -= DamageAmount;
        if (CurrentHealth <= 0){
            CurrentHealth = 0;
        }
    }

#pragma endregion