#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRAbilityBarWidget.generated.h"

class UDRGameplayAbility;

UCLASS()
class DEADRAIN_API UDRAbilitySlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void SetAbility(TSubclassOf<UDRGameplayAbility> NewValue);

protected:

};

UCLASS()
class DEADRAIN_API UDRAbilityBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void AddAbility(TSubclassOf<UDRGameplayAbility> NewValue);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void RemoveAbility(TSubclassOf<UDRGameplayAbility> NewValue);

protected:
    UPROPERTY()
    TArray<UDRAbilitySlotWidget*> AbilitySlots;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="DeadRain")
    TSubclassOf<UDRAbilitySlotWidget> AbilitySlotWidget;


};