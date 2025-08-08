// DRAbilitySlot.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayAbilitySpec.h"
#include "DRAbilitySlot.generated.h"

class UDRGameplayAbility;
class UDRAbilitySystemComponent;

UCLASS(BlueprintType, Blueprintable)
class UDRAbilitySlot : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION()
        virtual bool SetAbilitySystemComponent(UDRAbilitySystemComponent* InASC);
    UFUNCTION(BlueprintCallable)
        virtual bool SetAbilityClass(TSubclassOf<UDRGameplayAbility> InAbilityClass);
    UFUNCTION(BlueprintCallable)
        virtual bool ClearAbilityClass();
    UFUNCTION(BlueprintCallable)
        virtual bool ActivateAbility();

    UFUNCTION(BlueprintCallable)
        virtual bool IsActivatable() const { return bIsActivatable; }

protected:
    UPROPERTY()
        bool bIsActivatable = false;

    UPROPERTY()
        TWeakObjectPtr<UDRAbilitySystemComponent> ASC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UDRGameplayAbility> AbilityClass;

    UPROPERTY()
        FGameplayAbilitySpecHandle AbilityHandle;

};