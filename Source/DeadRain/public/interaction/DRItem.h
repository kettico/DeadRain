#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interaction/DRInteractableActor.h"
#include "DRItem.generated.h"

class ADRBaseCharacter;

UCLASS()
class DEADRAIN_API ADRItem : public ADRInteractableActor
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRItem();

    protected:
        virtual void BeginPlay() override;
        
#pragma endregion

#pragma region INTERFACE
    public:
        virtual void InteractPress(ADRBaseCharacter* Interactor);
        virtual void InteractHold(ADRBaseCharacter* Interactor);

        void OnPrePickup();
        void OnPostPickup();

        void OnPreDrop();
        void OnPostDrop();
    

#pragma endregion

#pragma region DATA
    public:
        UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
        void ApplyItem(ADRBaseCharacter* Interactor);

        UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
        void IncreaseCount(int32 Amount);

        UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
        void DecreaseCount(int32 Amount);
    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
        int32 Count = 1;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
        bool bIsStackable = false;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
        bool bIsConsumable = false;
#pragma endregion
};