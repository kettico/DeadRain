#include "weapon/gun/DRBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "character/DRBaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayEffect.h"

#pragma region CORE
    ADRBullet::ADRBullet(){
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

        Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
        Mesh->SetupAttachment(RootComponent);

        CollisionCapsule =  CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
        CollisionCapsule->SetupAttachment(RootComponent);

        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        
        PrimaryActorTick.bCanEverTick = true;
    }

    void ADRBullet::BeginPlay(){
        Super::BeginPlay();

        if (CollisionCapsule) 
            CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ADRBullet::OnCollisionBegin);
        

        if (!GameplayEffect)
            UE_LOG(LogTemp, Warning, TEXT("GameplayEffect is not set for %s"), *GetName());
        
        ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * 100.0f);
    }

    void ADRBullet::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult){
        if (!OtherActor) return;

        // Ignore collision with owner
        if (OtherActor == GetOwner()) return;

        if (ADRBaseCharacter* TargetCharacter = Cast<ADRBaseCharacter>(OtherActor)){
            if (ADRBaseCharacter* OwnerCharacter = Cast<ADRBaseCharacter>(GetOwner())){
                OwnerCharacter->ApplyGameplayEffectToTarget(GameplayEffect, TargetCharacter);
                Destroy();
            } 
        }
    }


#pragma endregion



