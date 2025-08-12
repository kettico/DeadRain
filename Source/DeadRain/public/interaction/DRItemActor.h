#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interaction/DRInteractableActor.h"
#include "DRItemActor.generated.h"

class ADRBaseCharacter;
class UDRItemData; 
UCLASS()
class DEADRAIN_API ADRItemActor : public ADRInteractableActor
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRItemActor();

    protected:
        virtual void BeginPlay() override;
        
#pragma endregion

#pragma region INTERFACE
    public:
        virtual void InteractPress_Implementation(ADRBaseCharacter* Interactor) override;
        virtual void InteractHold_Implementation(ADRBaseCharacter* Interactor) override;

        void OnPrePickup();
        void OnPostPickup();

        void OnPreDrop();
        void OnPostDrop();
    protected:
        virtual void TryAddItem(ADRBaseCharacter* Interactor);
#pragma endregion

#pragma region DATA
    public:
    protected:
        UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Data")
            UDRItemData* ItemData;
#pragma endregion
};