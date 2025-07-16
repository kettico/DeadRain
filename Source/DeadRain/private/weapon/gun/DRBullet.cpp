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

        CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
        CollisionCapsule->InitCapsuleSize(5.0f, 10.0f);
        CollisionCapsule->SetupAttachment(Mesh);

         if(!ProjectileMovementComponent)
        {
            ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
            ProjectileMovementComponent->SetUpdatedComponent(CollisionCapsule);
            ProjectileMovementComponent->InitialSpeed = 3000.0f;
            ProjectileMovementComponent->MaxSpeed = 3000.0f;
            ProjectileMovementComponent->bRotationFollowsVelocity = true;
            ProjectileMovementComponent->bShouldBounce = true;
            ProjectileMovementComponent->Bounciness = 0.3f;
            ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
        }

        PrimaryActorTick.bCanEverTick = true;
    }

    void ADRBullet::BeginPlay(){
        Super::BeginPlay();

        if (CollisionCapsule){
            CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ADRBullet::OnCollisionBegin);
        }

        ProjectileMovementComponent->Velocity = GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed;

        if (!GameplayEffect){
            UE_LOG(LogTemp, Warning, TEXT("GameplayEffect is not set for %s"), *GetName());
        }
    }

    void ADRBullet::Tick( float DeltaTime ){
        Super::Tick( DeltaTime );
 
    }

    void ADRBullet::OnCollisionBegin(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    ){

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

#pragma region 

#pragma endregion

