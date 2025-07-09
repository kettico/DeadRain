#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRInteractionPrompt.generated.h"

class ADRInteractableActor;

UCLASS()
class DEADRAIN_API UDRInteractionPrompt : public UUserWidget
{
    GENERATED_BODY()

public:


    UFUNCTION(BlueprintCallable)
    void SetInteractable(ADRInteractableActor* IA);

protected:

    ADRInteractableActor* CurrentInteractable;
};