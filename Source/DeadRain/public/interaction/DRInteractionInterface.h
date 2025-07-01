#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DRInteractionInterface.generated.h"

class ADRBaseCharacter;

UINTERFACE(MinimalAPI)
class UDRInteractionInterface : public UInterface
{
    GENERATED_BODY()
};

class DEADRAIN_API IDRInteractionInterface
{
    GENERATED_BODY()

#pragma region INTERFACE
    public:
        virtual void InteractPress(ADRBaseCharacter* Interactor) = 0;
        virtual void InteractHold(ADRBaseCharacter* Interactor) = 0;
        virtual bool IsInteractable() const = 0;
        virtual void ShowInteractionPrompt(APlayerController* PlayerController, bool Show) = 0;
#pragma endregion
};
