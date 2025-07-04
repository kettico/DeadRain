#include "character/DRBaseCharacter.h"
#include "weapon/DRWeapon.h"
#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"
#include "GameplayEffect.h"
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

#pragma region GAS

UAbilitySystemComponent* ADRBaseCharacter::GetAbilitySystemComponent() const{
    return AbilitySystemComponent.Get();
}

float ADRBaseCharacter::GetCurrentHealth() const{
    return 0.0;
}
float ADRBaseCharacter::GetMaxHealth() const{
    return  0.0;
}

void ADRBaseCharacter::InitializeGAS(){
    if(GetLocalRole() != ROLE_Authority)
        return;
    if (!AbilitySystemComponent.IsValid())
        return;

    // Add Startup Attributes
    if (!StartupAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}
	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(StartupAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
        
    // Add Startup Effects
	EffectContext.AddSourceObject(this);
	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}


}


#pragma endregion