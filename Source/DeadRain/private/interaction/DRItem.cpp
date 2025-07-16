#include "interaction/DRItem.h"
#include "character/DRBaseCharacter.h"

#pragma region CORE
    ADRItem::ADRItem(){

    }

    void ADRItem::BeginPlay(){
        Super::BeginPlay();
    }
#pragma endregion

#pragma region INTERFACE
    void ADRItem::InteractPress(ADRBaseCharacter* Interactor){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!IsInteractable()) return;
    }

    void ADRItem::InteractHold(ADRBaseCharacter* Interactor){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!IsInteractable()) return;
    }

    void ADRItem::OnPrePickup(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));
        

    }
    void ADRItem::OnPostPickup(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

    }

    void ADRItem::OnPreDrop(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

    }
    void ADRItem::OnPostDrop(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

    }
#pragma endregion
