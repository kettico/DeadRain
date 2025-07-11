#include "weapon/gun/DRBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "character/DRBaseCharacter.h"

#pragma region CORE
    ADRBullet::ADRBullet(){
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
       
        Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
        Mesh->SetupAttachment(RootComponent);

        CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
        CollisionCapsule->InitCapsuleSize(5.0f, 10.0f);
        CollisionCapsule->SetupAttachment(Mesh);

         PrimaryActorTick.bCanEverTick = true;
    }

    void ADRBullet::BeginPlay(){
        Super::BeginPlay();

        if (CollisionCapsule){
            CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ADRBullet::OnCollisionBegin);
        }//
    }//

    void ADRBullet::OnCollisionBegin(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    ){
        if (!OtherActor) return;

        if (ADRBaseCharacter* TargetCharacter = Cast<ADRBaseCharacter>(OtherActor)){
            
            Destroy();
        }
    }




#pragma endregion

#pragma region 

#pragma endregion
    
