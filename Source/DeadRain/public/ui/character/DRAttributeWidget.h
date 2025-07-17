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
	void SetCurrentHealth(float CurrentHealth);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

protected:


};