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


        void ADRPlayerState::CurrentMoneyChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

            UE_LOG( LogTemp, Warning, TEXT("CurrentMoneyChanged: %f"), Data.NewValue);
            float CurrentMoney = Data.NewValue;
            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetCurrentMoney(CurrentMoney);
                }

            }
        }

    #pragma endregion

#pragma endregion




