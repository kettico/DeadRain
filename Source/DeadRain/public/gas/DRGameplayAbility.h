#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DRGameplayAbility.generated.h"

class UTexture2D;

UCLASS()
class DEADRAIN_API UDRGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()
public:
    UDRGameplayAbility();


    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
    UTexture2D* AbilityIcon;

    UFUNCTION(BlueprintCallable, Category = "UI")
    UTexture2D* GetAbilityIcon() const { return AbilityIcon; }
};