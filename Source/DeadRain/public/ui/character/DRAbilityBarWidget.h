#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRAbilityBarWidget.generated.h"

class UDRGameplayAbility;
class UDRAbilitySlotWidget;


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