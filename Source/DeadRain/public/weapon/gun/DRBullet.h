#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRBullet.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

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
    UCapsuleComponent* CollisionCapsule;

    UFUNCTION()
    void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion

#pragma region 
    public:
        
    protected:

#pragma endregion
    
};