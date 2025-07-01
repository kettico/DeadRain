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
        if (!IsInteractable()) return;
    }

    void ADRItem::InteractHold(ADRBaseCharacter* Interactor){
        if (!IsInteractable()) return;
    }

    void ADRItem::OnPrePickup(){

    }
    void ADRItem::OnPostPickup(){

    }

    void ADRItem::OnPreDrop(){

    }
    void ADRItem::OnPostDrop(){

    }
#pragma endregion
