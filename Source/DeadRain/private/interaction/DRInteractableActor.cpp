#include "interaction/DRInteractableActor.h"
#include "character/DRBaseCharacter.h"
#include "Blueprint/UserWidget.h" // Add this include for CreateWidget

#pragma region CORE
    

    ADRInteractableActor::ADRInteractableActor(){
    }

    void ADRInteractableActor::BeginPlay(){
        Super::BeginPlay();


    }
        
#pragma endregion

#pragma region INTERFACE
    void ADRInteractableActor::InteractPress_Implementation(ADRBaseCharacter* Interactor){
    }

    void ADRInteractableActor::InteractHold_Implementation(ADRBaseCharacter* Interactor){
        
    }
    
    bool ADRInteractableActor::IsInteractable()const {
        return bIsInteractable;
    }
    void ADRInteractableActor::ShowInteractionPrompt(APlayerController* PlayerController, bool Show){

    }
#pragma endregion