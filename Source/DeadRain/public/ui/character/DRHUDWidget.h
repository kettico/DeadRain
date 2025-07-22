#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRHUDWidget.generated.h"

class ADRInteractableActor;
class UDRAttributeWidget;
class UDRAbilityBarWidget;
class UDRGameplayAbility;
class UDRStatWidget;

UCLASS()
class DEADRAIN_API UDRHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;


protected:


    UPROPERTY(meta = (BindWidget))
    UDRAbilityBarWidget* AbilityBarWidget;

    UPROPERTY(meta = (BindWidget))
    UDRStatWidget* StatWidget;


    #pragma region INPUTS
        public:
            UFUNCTION(BlueprintCallable)
            void ToggleStatMenu();
        protected:
    #pragma endregion

    #pragma region INTERACTION
        public:
            UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
            void SetCurrentInteractable(ADRInteractableActor* IA);
        protected:
    #pragma endregion


    #pragma region ATTRIBUTES
        public:
            UFUNCTION(BlueprintCallable)
            void AddAbility(TSubclassOf<UDRGameplayAbility> NewValue);
            UFUNCTION(BlueprintCallable)
            void RemoveAbility(TSubclassOf<UDRGameplayAbility> NewValue);
        protected:
    #pragma endregion

    #pragma region ATTRIBUTES

        #pragma region HEALTH
            public:
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetCurrentHealth(float NewValue);
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetMaxHealth(float NewValue);
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetHealthRegen(float NewValue);
            protected:  
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float CurrentHealth = -1.0f;
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float MaxHealth = -1.0f;
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float HealthRegen = -1.0f;
        #pragma endregion

        #pragma region Stamina 
            public:
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetCurrentStamina(float NewValue);
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetMaxStamina(float NewValue);
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetStaminaRegen(float NewValue);
            protected:   
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float CurrentStamina = -1.0f;
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float MaxStamina = -1.0f;
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float StaminaRegen = -1.0f;
        #pragma endregion

        #pragma region Mana  
            public:
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetCurrentMana(float NewValue);
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetMaxMana(float NewValue);
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetManaRegen(float NewValue);
            protected:  
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float CurrentMana = -1.0f;
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float MaxMana = -1.0f;
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float ManaRegen = -1.0f;
        #pragma endregion

        #pragma region Money  
            public:
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetCurrentMoney(float NewValue);
            protected:  
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float CurrentMoney = -1.0f;
        #pragma endregion

        #pragma region Ability  
            public:
                UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
                void SetAbilityHaste(float NewValue);
            protected:  
                UPROPERTY(BlueprintReadWrite , Category = "GAS|Attributes")
                float AbilityHaste = -1.0f;
        #pragma endregion


    #pragma endregion
    
};