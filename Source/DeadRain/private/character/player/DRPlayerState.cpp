#include "character/player/DRPlayerState.h"
#include "gas/DRAbilitySystemComponent.h"
#include "gas/attribute/DRCharacterSet.h"

#include "character/player/DRPlayerController.h"
#include "ui/character/DRHUDWidget.h"

#pragma region CORE
    ADRPlayerState::ADRPlayerState(){
        AbilitySystemComponent = CreateDefaultSubobject<UDRAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	    AbilitySystemComponent->SetIsReplicated(true);
        AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

        CharacterSet = CreateDefaultSubobject<UDRCharacterSet>(TEXT("CharacterSet"));

        SetNetUpdateFrequency(100.0f);
    }

    void ADRPlayerState::BeginPlay(){
        Super::BeginPlay();

        if (AbilitySystemComponent){

            CurrentMoneyChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetCurrentMoneyAttribute()).AddUObject(this, &ADRPlayerState::CurrentMoneyChanged);
        }
    }
#pragma endregion

#pragma region GAS

    UAbilitySystemComponent* ADRPlayerState::GetAbilitySystemComponent() const {
        return AbilitySystemComponent;
    }

    UDRAbilitySystemComponent* ADRPlayerState::GetDRAbilitySystemComponent() const{
        return AbilitySystemComponent;
    }


    UDRCharacterSet * ADRPlayerState::GetCharacterSet() const{
        return CharacterSet;
    }


    #pragma region GAS - Attributes
        float ADRPlayerState::GetCurrentHealth() const {
            return CharacterSet->GetCurrentHealth();
        }

        float ADRPlayerState::GetMaxHealth() const {
            return CharacterSet->GetMaxHealth();
        }

        float ADRPlayerState::GetHealthRegen() const {
            return CharacterSet->GetHealthRegen();
        }

        // STAMINA
        float ADRPlayerState::GetCurrentStamina() const {
            return CharacterSet->GetCurrentStamina();
        }

        float ADRPlayerState::GetMaxStamina() const {
            return CharacterSet->GetMaxStamina();
        }

        float ADRPlayerState::GetStaminaRegen() const {
            return CharacterSet->GetStaminaRegen();
        }

        // MANA
        float ADRPlayerState::GetCurrentMana() const {
            return CharacterSet->GetCurrentMana();
        }

        float ADRPlayerState::GetMaxMana() const {
            return CharacterSet->GetMaxMana();
        }

        float ADRPlayerState::GetManaRegen() const {
            return CharacterSet->GetManaRegen();
        }

        float ADRPlayerState::GetCurrentMoney() const {
            return CharacterSet->GetCurrentMoney();
        }


        void ADRPlayerState::CurrentMoneyChanged(const FOnAttributeChangeData& Data){

        }

    #pragma endregion

#pragma endregion




