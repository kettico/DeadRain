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
        virtual void InteractPress(ADRBaseCharacter* Interactor) {}
        virtual void InteractHold(ADRBaseCharacter* Interactor) {}
        virtual bool IsInteractable() const { return true; }
        virtual void ShowInteractionPrompt(APlayerController* PlayerController, bool Show) {}
#pragma endregion
};
