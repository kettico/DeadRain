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
            CurrentHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetCurrentHealthAttribute()).AddUObject(this, &ADRPlayerState::CurrentHealthChanged);
            MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetMaxHealthAttribute()).AddUObject(this, &ADRPlayerState::MaxHealthChanged);
            HealthRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetHealthRegenAttribute()).AddUObject(this, &ADRPlayerState::HealthRegenChanged);
            
            CurrentMoneyChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetCurrentMoneyAttribute()).AddUObject(this, &ADRPlayerState::CurrentMoneyChanged);
        }
    }
#pragma endregion

#pragma region GAS


    UAbilitySystemComponent* ADRPlayerState::GetAbilitySystemComponent() const{
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

        float ADRPlayerState::GetCurrentMoney() const {
            return CharacterSet->GetCurrentMoney();
        }

        void ADRPlayerState::CurrentHealthChanged(const FOnAttributeChangeData& Data){
            float CurrentHealth = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetCurrentHealth(CurrentHealth);
                }
            }
        }

        void ADRPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data){
            float MaxHealth = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetMaxHealth(MaxHealth);
                }
            }
        }
        void ADRPlayerState::HealthRegenChanged(const FOnAttributeChangeData& Data){

        }

        void ADRPlayerState::CurrentMoneyChanged(const FOnAttributeChangeData& Data){
            float CurrentMoney = Data.NewValue;
            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetCurrentMoney(CurrentMoney);
                }

            }
        }

    #pragma endregion

#pragma endregion




