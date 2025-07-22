#include "ui/character/DRHUDWidget.h"
#include "ui/character/DRAttributeWidget.h"

#include "interaction/DRInteractableActor.h"
#include "ui/character/DRAbilityBarWidget.h"

#include "ui/character/DRStatWidget.h"

void UDRHUDWidget::NativeConstruct(){
    Super::NativeConstruct();
}



#pragma region ATTRIBUTES
    void UDRHUDWidget::AddAbility(TSubclassOf<UDRGameplayAbility> NewValue){
    if (AbilityBarWidget)
        AbilityBarWidget->AddAbility(NewValue);
    }
    void UDRHUDWidget::RemoveAbility(TSubclassOf<UDRGameplayAbility> NewValue){
        if (AbilityBarWidget)
            AbilityBarWidget->RemoveAbility(NewValue);
    }
#pragma endregion






#pragma region ATTRIBUTES

    #pragma region HEALTH
        void UDRHUDWidget::SetCurrentHealth_Implementation(float NewValue){
            CurrentHealth = NewValue;
        }
        void UDRHUDWidget::SetMaxHealth_Implementation(float NewValue){
            MaxHealth = NewValue;
        }
        void UDRHUDWidget::SetHealthRegen_Implementation(float NewValue){
            HealthRegen = NewValue;
        }
    #pragma endregion

    #pragma region Stamina 
            void UDRHUDWidget::SetCurrentStamina_Implementation(float NewValue){
            CurrentStamina = NewValue;
        }
            void UDRHUDWidget::SetMaxStamina_Implementation(float NewValue){
            MaxStamina = NewValue;
        }
            void UDRHUDWidget::SetStaminaRegen_Implementation(float NewValue){
            StaminaRegen = NewValue;
        }
    #pragma endregion

    #pragma region Mana  
            void UDRHUDWidget::SetCurrentMana_Implementation(float NewValue){
            CurrentMana = NewValue;
        }
            void UDRHUDWidget::SetMaxMana_Implementation(float NewValue){
            MaxMana = NewValue;
        }
            void UDRHUDWidget::SetManaRegen_Implementation(float NewValue){
            ManaRegen = NewValue;
        }
    #pragma endregion

    #pragma region Money  
        void UDRHUDWidget::SetCurrentMoney_Implementation(float NewValue){
            CurrentMoney = NewValue;
        }
    #pragma endregion

    #pragma region Ability  
        void UDRHUDWidget::SetAbilityHaste_Implementation(float NewValue){
            AbilityHaste = NewValue;
        }
    #pragma endregion


#pragma endregion


#pragma region INPUTS
    void UDRHUDWidget::ToggleStatMenu() {
        if (StatWidget) {
            ESlateVisibility CurrentVisibility = StatWidget->GetVisibility();
            StatWidget->SetVisibility(
                CurrentVisibility == ESlateVisibility::Visible
                ? ESlateVisibility::Collapsed
                : ESlateVisibility::Visible
            );
        }
    }
#pragma endregion