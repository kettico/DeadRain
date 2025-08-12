#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DRCharacterSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DEADRAIN_API UDRCharacterSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UDRCharacterSet();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    
    UPROPERTY(BlueprintReadOnly, Category = "IncomingDamage", ReplicatedUsing = OnRep_IncomingDamage)
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UDRCharacterSet, IncomingDamage)

    #pragma region HEALTH
        UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_CurrentHealth)
        FGameplayAttributeData CurrentHealth;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, CurrentHealth)
        
        UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
        FGameplayAttributeData MaxHealth;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, MaxHealth)

        UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthRegen)
        FGameplayAttributeData HealthRegen;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, HealthRegen)
    #pragma endregion

    #pragma region STAMINA
        UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_CurrentStamina)
        FGameplayAttributeData CurrentStamina;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, CurrentStamina)
        
        UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_MaxStamina)
        FGameplayAttributeData MaxStamina;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, MaxStamina)

        UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_StaminaRegen)
        FGameplayAttributeData StaminaRegen;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, StaminaRegen)
    #pragma endregion

    #pragma region MANA
        UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_CurrentMana)
        FGameplayAttributeData CurrentMana;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, CurrentMana)
        
        UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
        FGameplayAttributeData MaxMana;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, MaxMana)

        UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_ManaRegen)
        FGameplayAttributeData ManaRegen;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, ManaRegen)
    #pragma endregion

    #pragma region MONEY
        UPROPERTY(BlueprintReadOnly, Category = "Money", ReplicatedUsing = OnRep_CurrentMoney)
        FGameplayAttributeData CurrentMoney;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, CurrentMoney)
    #pragma endregion

    #pragma region ABILITIES
        UPROPERTY(BlueprintReadOnly, Category = "Ability", ReplicatedUsing = OnRep_AbilityHaste)
        FGameplayAttributeData AbilityHaste;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, AbilityHaste)
    #pragma endregion


    #pragma region Weapon
        UPROPERTY(BlueprintReadOnly, Category = "Ability", ReplicatedUsing = OnRep_AttackSpeed)
        FGameplayAttributeData AttackSpeed;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, AttackSpeed)
    #pragma endregion 

    #pragma region Movement
        UPROPERTY(BlueprintReadOnly, Category = "Ability", ReplicatedUsing = OnRep_MoveSpeed)
        FGameplayAttributeData MoveSpeed;
        ATTRIBUTE_ACCESSORS(UDRCharacterSet, MoveSpeed)

    #pragma endregion 

    

protected:
    void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

    UFUNCTION()
    void OnRep_IncomingDamage(const FGameplayAttributeData& OldValue);

        

    #pragma region HEALTH
        UFUNCTION()
        void OnRep_CurrentHealth(const FGameplayAttributeData& OldValue);
        UFUNCTION()
        void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
        UFUNCTION()
        void OnRep_HealthRegen(const FGameplayAttributeData& OldValue);
    #pragma endregion

    #pragma region STAMINA
        UFUNCTION()
        void OnRep_CurrentStamina(const FGameplayAttributeData& OldValue);
        UFUNCTION()
        void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
        UFUNCTION()
        void OnRep_StaminaRegen(const FGameplayAttributeData& OldValue);
    #pragma endregion

    #pragma region MANA
        UFUNCTION()
        void OnRep_CurrentMana(const FGameplayAttributeData& OldValue);
        UFUNCTION()
        void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
        UFUNCTION()
        void OnRep_ManaRegen(const FGameplayAttributeData& OldValue);
    #pragma endregion

    #pragma region MONEY
        UFUNCTION()
        void OnRep_CurrentMoney(const FGameplayAttributeData& OldValue);
    #pragma endregion

    #pragma region ABILITIES
        UFUNCTION()
        void OnRep_AbilityHaste(const FGameplayAttributeData& OldValue);
    #pragma endregion

    #pragma region Weapon
        UFUNCTION()
        void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue);
    #pragma endregion

    #pragma region Movement
        UFUNCTION()
        void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);
    #pragma endregion

};