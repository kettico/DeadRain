#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRHUDWidget.generated.h"

class ADRInteractableActor;
class UDRAttributeWidget;

UCLASS()
class DEADRAIN_API UDRHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float NewValue);
    UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float NewValue);

    UFUNCTION(BlueprintCallable)
	void SetCurrentStamina(float NewValue);
    UFUNCTION(BlueprintCallable)
	void SetMaxStamina(float NewValue);

    UFUNCTION(BlueprintCallable)
	void SetCurrentMana(float NewValue);
     UFUNCTION(BlueprintCallable)
	void SetMaxMana(float NewValue);


    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMoney(float NewValue);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void SetCurrentInteractable(ADRInteractableActor* IA);

protected:

    UPROPERTY(meta = (BindWidget))
    UDRAttributeWidget* AttributeWidget;


};