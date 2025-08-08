#include "gas/ability/DRAbilitySlot.h"
#include "gas/DRGameplayAbility.h"
#include "gas/DRAbilitySystemComponent.h"


bool UDRAbilitySlot::SetAbilitySystemComponent(UDRAbilitySystemComponent* InASC){
    if (!InASC) return false;

    ASC = InASC;

    return true;
}

bool UDRAbilitySlot::SetAbilityClass(TSubclassOf<UDRGameplayAbility> InAbilityClass){
    if (!InAbilityClass) return false;

    AbilityClass = InAbilityClass;

    if (!ASC.IsValid()) return false;

    AbilityHandle = ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this));
    if (!AbilityHandle.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to give ability %s to ASC %s"), *GetNameSafe(AbilityClass), *GetNameSafe(ASC.Get()));
        return false;
    }

    bIsActivatable = true;
    return true;
}
bool UDRAbilitySlot::ClearAbilityClass(){
    AbilityClass = nullptr;

    if (!ASC.IsValid() || !AbilityHandle.IsValid())
        return false;

    ASC->ClearAbility(AbilityHandle);
    AbilityHandle = FGameplayAbilitySpecHandle();
    
    bIsActivatable = false;
    return true;
}
bool UDRAbilitySlot::ActivateAbility(){
    if (!ASC.IsValid() || !AbilityHandle.IsValid())
        return false;

    if (!bIsActivatable) return false;

    if (!ASC->TryActivateAbility(AbilityHandle))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to activate ability %s"), *GetNameSafe(AbilityClass));
        return false;
    }

    return true;
}

