#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRAbilitySlotWidget.generated.h"

class UDRGameplayAbility;

class UImage;
class UTextBlock;

UCLASS()
class DEADRAIN_API UDRAbilitySlotWidget : public UUserWidget
{
    GENERATED_BODY()

#pragma region "COMPONENTS"
    protected:
        UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
            UImage* Icon;
        UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
            UTextBlock* CooldownText;
        UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
            UTextBlock* InputText;
        UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
            UTextBlock* CounterText;
#pragma endregion

#pragma region "Ability"
    public:
        UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
            void SetAbility(TSubclassOf<UDRGameplayAbility> NewValue);
        
    protected:
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "DEADRAIN")
            TSubclassOf<UDRGameplayAbility> Ability;
#pragma endregion
};