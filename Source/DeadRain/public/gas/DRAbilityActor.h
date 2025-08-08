#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRAbilityActor.generated.h"

class UStaticMeshComponent;
class UDRGameplayAbility;

UCLASS()
class DEADRAIN_API ADRAbilityActor : public AActor
{
    GENERATED_BODY()

public:
    ADRAbilityActor();

    UFUNCTION(BlueprintCallable, Category = "DeadRain|AbilityPickup")
        TSubclassOf<UDRGameplayAbility> GetAbilityClass() const { return AbilityClass; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DeadRain|AbilityPickup")
        UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeadRain|AbilityPickup")
        TSubclassOf<UDRGameplayAbility> AbilityClass;
};