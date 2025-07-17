#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemInterface.h"
#include "DRPlayerState.generated.h"

class UDRAbilitySystemComponent;
class UDRCharacterSet;

UCLASS()
class DEADRAIN_API ADRPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRPlayerState();

    protected:
        virtual void BeginPlay() override;

#pragma endregion

#pragma region GAS
public:
    UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UDRCharacterSet* GetCharacterSet() const;

    

protected:
    UPROPERTY()
	UDRAbilitySystemComponent* AbilitySystemComponent;
    UPROPERTY()
	UDRCharacterSet* CharacterSet;

    #pragma region GAS - Attributes
    public:
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetCurrentHealth() const;
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetMaxHealth() const;
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetHealthRegen() const;

                UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetCurrentStamina() const;
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetMaxStamina() const;
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetStaminaRegen() const;

                UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetCurrentMana() const;
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetMaxMana() const;
        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetManaRegen() const;


        UFUNCTION(BlueprintCallable, Category = "GAS|Player|State|Attributes")
        float GetCurrentMoney() const;

    protected:

        FDelegateHandle CurrentMoneyChangedDelegateHandle;
        virtual void CurrentMoneyChanged(const FOnAttributeChangeData& Data);

        
	    
	    
    #pragma endregion

#pragma endregion


};