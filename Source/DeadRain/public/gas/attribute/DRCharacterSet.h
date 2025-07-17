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

    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UDRCharacterSet, CurrentHealth)
    
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDRCharacterSet, MaxHealth)

    
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UDRCharacterSet, HealthRegen)

    UPROPERTY(BlueprintReadOnly, Category = "Money", ReplicatedUsing = OnRep_CurrentMoney)
	FGameplayAttributeData CurrentMoney;
	ATTRIBUTE_ACCESSORS(UDRCharacterSet, CurrentMoney)

protected:
    void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

    UFUNCTION()
    void OnRep_IncomingDamage(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_CurrentHealth(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    void OnRep_HealthRegen(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_CurrentMoney(const FGameplayAttributeData& OldValue);
};