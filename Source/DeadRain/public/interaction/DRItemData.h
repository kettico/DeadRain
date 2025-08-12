// DRItemData.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"  // For UDataAsset base class
#include "DRItemData.generated.h"

class ADRItemActor;

UCLASS(BlueprintType)
class DEADRAIN_API UDRItemData : public UDataAsset
{
    GENERATED_BODY()

public:
    UDRItemData();
    UFUNCTION(BlueprintCallable, Category = "Actor")
        TSubclassOf<ADRItemActor> GetItemActorClass() const { return ItemActorClass; }
    UFUNCTION(BlueprintCallable, Category = "Actor")
        void SetItemActorClass(TSubclassOf<ADRItemActor> NewActor) { ItemActorClass = NewActor;}
    
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
        TSubclassOf<class UGameplayEffect> GetGameplayEffectClass() const { return GameplayEffectClass; }
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor")
        TSubclassOf<ADRItemActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
        TSubclassOf<class UGameplayEffect> GameplayEffectClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic")
        FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta=(MultiLine=true))
        FText Description;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic")
        UTexture2D* Icon;
};
