#include "interaction/DRItemActor.h"

#include "character/DRBaseCharacter.h"
#include "interaction/DRItemManagerComponent.h"
#include "interaction/DRItemData.h"

DEFINE_LOG_CATEGORY_STATIC(LogDRItemActor, Log, All);

#pragma region CORE
    ADRItemActor::ADRItemActor(){

    }

    void ADRItemActor::BeginPlay(){
        Super::BeginPlay();

        if (ItemData)
            ItemData->SetItemActorClass(GetClass());
    }
#pragma endregion

#pragma region INTERFACE
    void ADRItemActor::InteractPress_Implementation(ADRBaseCharacter* Interactor){
        TryAddItem(Interactor);
    }

    void ADRItemActor::InteractHold_Implementation(ADRBaseCharacter* Interactor){
        TryAddItem(Interactor);
    }

    void ADRItemActor::TryAddItem(ADRBaseCharacter* Interactor){
        if (!IsInteractable()) return;

        if (ADRBaseCharacter* Character = Cast<ADRBaseCharacter>(Interactor)){
            if (UDRItemManagerComponent* ItemManager = Character->GetItemManager()){
                if (ItemData){
                    if (ItemManager->AddItem(ItemData))
                        Destroy();
                }
            }
        }
    }

    void ADRItemActor::OnPrePickup(){
        UE_LOG(LogDRItemActor, Log, TEXT("[%s]"), TEXT(__FUNCTION__));
    }
    
    void ADRItemActor::OnPostPickup(){
        UE_LOG(LogDRItemActor, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        Destroy();
    }

    void ADRItemActor::OnPreDrop(){
        UE_LOG(LogDRItemActor, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

    }
    void ADRItemActor::OnPostDrop(){
        UE_LOG(LogDRItemActor, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

    }
#pragma endregion
