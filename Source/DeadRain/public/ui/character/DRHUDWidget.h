#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRHUDWidget.generated.h"

UCLASS()
class DEADRAIN_API UDRHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

protected:

};