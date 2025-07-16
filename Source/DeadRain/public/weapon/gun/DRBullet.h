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

    UFUNCTION()
    void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);


protected:
    virtual void BeginPlay() override;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* CollisionCapsule;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
    TSubclassOf<UGameplayEffect> GameplayEffect;

#pragma endregion


    
};