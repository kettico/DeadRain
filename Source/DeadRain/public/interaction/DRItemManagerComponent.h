#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRItemManagerComponent.generated.h"

class ADRBaseCharacter;
class ADRItemActor;
class UDRItemData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADRAIN_API UDRItemManagerComponent : public UActorComponent
{
    GENERATED_BODY()

#pragma region CORE
    public:	
        UDRItemManagerComponent();

    protected:
        virtual void BeginPlay() override;
#pragma endregion

#pragma region ITEMS
    public:	
        UFUNCTION(BlueprintCallable, Category = "Item Management")
            bool AddItem(UDRItemData* ItemData, int32 Amount = 1);
        UFUNCTION(BlueprintCallable, Category = "Item Management")
            bool RemoveItem(UDRItemData* ItemData, int32 Amount = 1);
        UFUNCTION(BlueprintCallable, Category = "Item Management")
            bool DropItem(UDRItemData* ItemData, int32 Amount = 1);
    protected:
        UFUNCTION()
            bool ApplyItem(UDRItemData* ItemData);
        UPROPERTY()
            TMap<UDRItemData*, int32> ItemMap;
#pragma endregion
};