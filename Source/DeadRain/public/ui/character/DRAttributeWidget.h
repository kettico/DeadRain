#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRAttributeWidget.generated.h"



UCLASS()
class DEADRAIN_API UDRAttributeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float NewValue);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float NewValue);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentStamina(float NewValue);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxStamina(float NewValue);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMana(float NewValue);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxMana(float NewValue);

protected:

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float CurrentHealth = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float MaxHealth = 0.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float CurrentStamina = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float MaxStamina = 0.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float CurrentMana = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float MaxMana = 0.0f;
    

};