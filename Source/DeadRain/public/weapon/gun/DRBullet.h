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
    virtual void Tick( float DeltaTime ) override;

protected:

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* CollisionCapsule;

    UPROPERTY(VisibleAnywhere, Category = Movement)
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
    TSubclassOf<UGameplayEffect> GameplayEffect;

    UFUNCTION()
    void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion

#pragma region 
    public:
        
    protected:

#pragma endregion
    
};