#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRBullet.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UProjectileMovementComponent;
class UGameplayEffect;

UCLASS()
class DEADRAIN_API ADRBullet : public AActor
{
    GENERATED_BODY()

#pragma region CORE
public:
    ADRBullet();

protected:
    virtual void BeginPlay() override;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* ProjectileMovementComponent;
#pragma endregion


    
};