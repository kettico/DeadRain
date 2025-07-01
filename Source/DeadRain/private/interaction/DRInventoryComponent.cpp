#include "interaction/DRInventoryComponent.h"
#include "interaction/DRItem.h"
#include "character/DRBaseCharacter.h"

#pragma region CORE
    UDRInventoryComponent::UDRInventoryComponent(){

    }

    void UDRInventoryComponent::BeginPlay(){
        Super::BeginPlay();
    }
#pragma endregion

#pragma region ITEMS
    void UDRInventoryComponent::AddItem(ADRItem* Item){

    }

    bool UDRInventoryComponent::RemoveItem(ADRItem* Item){
        return false;
    }

    bool UDRInventoryComponent::HasItem(ADRItem* Item) const{
        return false;
    }

    const TArray<ADRItem*>& UDRInventoryComponent::GetInventory() const{
        return Items;
    }
#pragma endregion
