#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ui/components/DRTextBlock.h"
#include "AbilitySystemComponent.h"
#include "DRFullAttributeWidget.generated.h"

class UDRAbilitySystemComponent;
struct FOnAttributeChangeData;

UCLASS()
class DEADRAIN_API UDRFullAttributeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void SetAbilitySystemComponent(UDRAbilitySystemComponent* asc);

protected:
    TWeakObjectPtr<UDRAbilitySystemComponent> ASC;


#pragma region ATTRIBUTES

    #pragma region HEALTH
        public:
            void OnCurrentHealthChanged(const FOnAttributeChangeData&  Data);
            void OnMaxHealthChanged(const FOnAttributeChangeData&  Data);
            void OnHealthRegenChanged(const FOnAttributeChangeData&  Data);

        protected:
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float CurrentHealth = -1.0f;
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float MaxHealth = -1.0f;
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float HealthRegen = -1.0f;
    #pragma endregion

    #pragma region Stamina
        public:
            void OnCurrentStaminaChanged(const FOnAttributeChangeData&  Data);
            void OnMaxStaminaChanged(const FOnAttributeChangeData&  Data);
            void OnStaminaRegenChanged(const FOnAttributeChangeData&  Data);

        protected:
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float CurrentStamina = -1.0f;
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float MaxStamina = -1.0f;
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float StaminaRegen = -1.0f;
    #pragma endregion

    #pragma region Mana
        public:
            void OnCurrentManaChanged(const FOnAttributeChangeData&  Data);
            void OnMaxManaChanged(const FOnAttributeChangeData&  Data);
            void OnManaRegenChanged(const FOnAttributeChangeData&  Data);

        protected:
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float CurrentMana = -1.0f;
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float MaxMana = -1.0f;
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float ManaRegen = -1.0f;
    #pragma endregion

    #pragma region Money
        public:
            void OnCurrentMoneyChanged(const FOnAttributeChangeData&  Data);
        protected:  
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float CurrentMoney = -1.0f;
    #pragma endregion 

    #pragma region Abilities
        public:
            void OnAbilityHasteChanged(const FOnAttributeChangeData&  Data);
        protected:  
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float AbilityHaste = -1.0f;
    #pragma endregion 

    #pragma region Weapon
        public:
            void OnAttackSpeedChanged(const FOnAttributeChangeData&  Data);
        protected:  
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float AttackSpeed = -1.0f;
    #pragma endregion 

    #pragma region Movement
        public:
            void OnMoveSpeedChanged(const FOnAttributeChangeData&  Data);
        protected:  
            UPROPERTY(BlueprintReadOnly, Category="Stat")
            float MoveSpeed = -1.0f;
    #pragma endregion 
#pragma endregion 

};

