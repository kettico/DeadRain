#include "interaction/DRItemManagerComponent.h"

#include "interaction/DRItemActor.h"
#include "interaction/DRItemData.h"
#include "character/DRBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogItemManager, Log, All);

#pragma region CORE
    UDRItemManagerComponent::UDRItemManagerComponent(){
        ItemMap.Empty();
    }

    void UDRItemManagerComponent::BeginPlay(){
        Super::BeginPlay();
    }
#pragma endregion

#pragma region "ITEMS"
    bool UDRItemManagerComponent::AddItem(UDRItemData* ItemData, int32 Amount){
        if (!ItemData || Amount <= 0) return false;
        
        if (ItemMap.Contains(ItemData)) {
            ItemMap[ItemData] += Amount; // Increase existing item count
            ApplyItem(ItemData);  
        } else {
            ItemMap.Add(ItemData, Amount); // Add new item with initial amount
            ApplyItem(ItemData);
        }

        return true;
    }
    
    bool UDRItemManagerComponent::RemoveItem(UDRItemData* ItemData, int32 Amount){
        if (!ItemData || Amount <= 0) return false;
        
        int32* CurrentAmount= ItemMap.Find(ItemData);
        if (!CurrentAmount || *CurrentAmount < Amount) 
            return false;

        *CurrentAmount -= Amount;
        return true;
    }
    
    bool UDRItemManagerComponent::DropItem(UDRItemData* ItemData, int32 Amount){
        if (!ItemData || Amount <= 0) return false;
        
        int32* CurrentAmount= ItemMap.Find(ItemData);
        if (!CurrentAmount || *CurrentAmount < Amount) 
            return false;

        *CurrentAmount -= Amount;

        //SpawnItemActor(ItemData, Amount);
        return true;
    }
    

    bool UDRItemManagerComponent::ApplyItem(UDRItemData* ItemData)
    {
        if (!ItemData) return false;
        
        ADRBaseCharacter* OwnerCharacter = Cast<ADRBaseCharacter>(GetOwner());
        if (!OwnerCharacter) return false;

        UAbilitySystemComponent* ASC = OwnerCharacter->GetAbilitySystemComponent();
        if (!ASC) return false;
        
        if (ItemData->GetGameplayEffectClass())
        {
            FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
            ContextHandle.AddSourceObject(this);

            FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ItemData->GetGameplayEffectClass(), 1.f, ContextHandle);
            if (SpecHandle.IsValid())
            {
                ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
                return true;
            }
        }
        return false;
    }
#pragma endregion
