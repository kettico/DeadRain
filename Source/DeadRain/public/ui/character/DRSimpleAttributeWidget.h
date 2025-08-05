#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ui/components/DRTextBlock.h"
#include "AbilitySystemComponent.h"
#include "DRSimpleAttributeWidget.generated.h"


class UProgressBar;
class UDRAbilitySystemComponent;

struct FOnAttributeChangeData;
/*
* Contain Text and Float of an attribute Value
*/
UCLASS()
class DEADRAIN_API UDRSimpleAttributeWidget : public UUserWidget
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
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentHealth = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float MaxHealth = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float HealthRegen = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentHealthPercent = 0.0f;
    #pragma endregion

    #pragma region Stamina
        public:
            void OnCurrentStaminaChanged(const FOnAttributeChangeData&  Data);
            void OnMaxStaminaChanged(const FOnAttributeChangeData&  Data);
            void OnStaminaRegenChanged(const FOnAttributeChangeData&  Data);

        protected:
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentStamina = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float MaxStamina = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float StaminaRegen = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentStaminaPercent = 0.0f;
    #pragma endregion

    #pragma region mana
        public:
            void OnCurrentManaChanged(const FOnAttributeChangeData&  Data);
            void OnMaxManaChanged(const FOnAttributeChangeData&  Data);
            void OnManaRegenChanged(const FOnAttributeChangeData&  Data);

        protected:
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentMana = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float MaxMana = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float ManaRegen = -1.0f;
            UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentManaPercent = 0.0f;
    #pragma endregion

#pragma endregion 

};

