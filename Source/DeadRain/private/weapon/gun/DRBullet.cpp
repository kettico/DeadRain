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

        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        
        PrimaryActorTick.bCanEverTick = true;
    }

    void ADRBullet::BeginPlay(){
        Super::BeginPlay();

        ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * 100.0f);
    }




#pragma endregion



