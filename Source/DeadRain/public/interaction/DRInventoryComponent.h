#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRInventoryComponent.generated.h"

class ADRBaseCharacter;
class ADRItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADRAIN_API UDRInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

#pragma region CORE
    public:	
        UDRInventoryComponent();

    protected:
        virtual void BeginPlay() override;
#pragma endregion

#pragma region ITEMS
public:	
        UFUNCTION(BlueprintCallable, Category = "Inventory")
        void AddItem(ADRItem* Item);

        UFUNCTION(BlueprintCallable, Category = "Inventory")
        bool RemoveItem(ADRItem* Item);

        UFUNCTION(BlueprintCallable, Category = "Inventory")
        bool HasItem(ADRItem* Item) const;

        UFUNCTION(BlueprintCallable, Category = "Inventory")
        const TArray<ADRItem*>& GetInventory() const;

    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<ADRItem*> Items;
#pragma endregion
};