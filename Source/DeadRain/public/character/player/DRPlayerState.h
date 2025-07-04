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
    protected:
        virtual void CurrentHealthChanged(const FOnAttributeChangeData& Data);
        virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
        virtual void HealthRegenChanged(const FOnAttributeChangeData& Data);
        FDelegateHandle CurrentHealthChangedDelegateHandle;
	    FDelegateHandle MaxHealthChangedDelegateHandle;
	    FDelegateHandle HealthRegenChangedDelegateHandle;
    #pragma endregion

#pragma endregion


};