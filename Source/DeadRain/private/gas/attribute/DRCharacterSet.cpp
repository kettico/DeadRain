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

	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, CurrentStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, StaminaRegen, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, CurrentMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, ManaRegen, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UDRCharacterSet, CurrentMoney, COND_None, REPNOTIFY_Always);
}

void UDRCharacterSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue){
    Super::PreAttributeChange(Attribute, NewValue);

    // On Max Change, adjust Current so it is the same % 
    if (Attribute == GetMaxHealthAttribute()) {
        //AdjustAttributeForMaxChange(CurrentHealth, MaxHealth, NewValue, GetCurrentHealthAttribute());
    } else if (Attribute == GetMaxStaminaAttribute()) {
	} else if (Attribute == GetMaxManaAttribute()) {
	}
}

void UDRCharacterSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data){

	Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ADRBaseCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ADRBaseCharacter>(TargetActor);
	}

	// Get the Source actor
	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	ADRBaseCharacter* SourceCharacter = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}

		// Use the controller to find the source pawn
		if (SourceController)
		{
			SourceCharacter = Cast<ADRBaseCharacter>(SourceController->GetPawn());
		}
		else
		{
			SourceCharacter = Cast<ADRBaseCharacter>(SourceActor);
		}

		// Set the causer actor based on context if it's set
		if (Context.GetEffectCauser())
		{
			SourceActor = Context.GetEffectCauser();
		}
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		if (LocalIncomingDamage > 0.0f){
			SetIncomingDamage(0.0f);

			const float OldHealth = GetCurrentHealth();
            const float NewHealth = FMath::Clamp(OldHealth - LocalIncomingDamage, 0.0f, GetMaxHealth());
            SetCurrentHealth(NewHealth);

            // Optional: Add logic for OnDeath or low health here
            if (OldHealth > 0.0f && NewHealth <= 0.0f)
            {
                TargetCharacter->Die();
            }
		}
	} else if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute()){
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth()));
	} else if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute()){
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(), 0.0f, GetMaxStamina()));
	} else if (Data.EvaluatedData.Attribute == GetCurrentManaAttribute()){
		SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.0f, GetMaxMana()));
	}

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




void UDRCharacterSet::OnRep_IncomingDamage(const FGameplayAttributeData& OldValue){
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, IncomingDamage, OldValue);
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


// STAMINA ----------------------------------------------------------------
void UDRCharacterSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, CurrentStamina, OldValue);
}
void UDRCharacterSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, MaxStamina, OldValue);
}
void UDRCharacterSet::OnRep_StaminaRegen(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, StaminaRegen, OldValue);
}

// Mana ----------------------------------------------------------------
void UDRCharacterSet::OnRep_CurrentMana(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, CurrentMana, OldValue);
}
void UDRCharacterSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, MaxMana, OldValue);
}
void UDRCharacterSet::OnRep_ManaRegen(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, ManaRegen, OldValue);
}

void UDRCharacterSet::OnRep_CurrentMoney(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, CurrentMoney, OldValue);
}

void UDRCharacterSet::OnRep_AbilityHaste(const FGameplayAttributeData& OldValue){
    GAMEPLAYATTRIBUTE_REPNOTIFY(UDRCharacterSet, AbilityHaste, OldValue);
}

