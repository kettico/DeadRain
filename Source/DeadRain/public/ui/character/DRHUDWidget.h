#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRHUDWidget.generated.h"

class ADRInteractableActor;
class UDRAttributeWidget;
class UDRAbilityBarWidget;
class UDRGameplayAbility;
class UDRStatWidget;
class UDRAbilitySystemComponent;
class UDRSimpleAttributeWidget;
class UDRFullAttributeWidget;

UCLASS()
class DEADRAIN_API UDRHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void SetAbilitySystemComponent(UDRAbilitySystemComponent* asc);

protected:
    TWeakObjectPtr<UDRAbilitySystemComponent> ASC;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UDRAbilityBarWidget* AbilityBarWidget;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UDRSimpleAttributeWidget* SimpleAttributeWidget;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UDRFullAttributeWidget* FullAttributeWidget;





    #pragma region INPUTS
        public:
        protected:
    #pragma endregion

    #pragma region INTERACTION
        public:
            UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
            void SetCurrentInteractable(ADRInteractableActor* IA);
        protected:
    #pragma endregion


    #pragma region ATTRIBUTES
        public:
            UFUNCTION(BlueprintCallable)
            void AddAbility(TSubclassOf<UDRGameplayAbility> NewValue);
            UFUNCTION(BlueprintCallable)
            void RemoveAbility(TSubclassOf<UDRGameplayAbility> NewValue);
        protected:
    #pragma endregion




    #pragma endregion
    
};