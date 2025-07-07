#include "gas/attribute/DRCharacterSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "character/DRBaseCharacter.h"
#include "character/player/DRPlayerController.h"


UDRCharacterSet::UDRCharacterSet(){

}

void UDRCharacterSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, HealthRegen, COND_None, REPNOTIFY_Always);
}

void UDRCharacterSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue){
    Super::PreAttributeChange(Attribute, NewValue);

    // On Max Change, adjust Current so it is the same % 
    if (Attribute == GetMaxHealthAttribute()) {
        //AdjustAttributeForMaxChange(CurrentHealth, MaxHealth, NewValue, GetCurrentHealthAttribute());
    } 
}

void UDRCharacterSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data){

	Super::PostGameplayEffectExecute(Data);

    //TODO:
}

// THIS DOESNT WORK
void UDRCharacterSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty){
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}



void UDRCharacterSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, CurrentHealth, OldValue);
}
void UDRCharacterSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, MaxHealth, OldValue);
}
void UDRCharacterSet::OnRep_HealthRegen(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, HealthRegen, OldValue);
}
