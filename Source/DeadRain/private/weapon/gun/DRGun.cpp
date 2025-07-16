#include "weapon/gun/DRGun.h"
#include "weapon/gun/DRBullet.h"

#pragma region CORE
    ADRGun::ADRGun(){


        MuzzleComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleComponent"));
        MuzzleComponent->SetupAttachment(WeaponMesh);

    }

    void ADRGun::BeginPlay()
    {
        Super::BeginPlay();

        if (!BulletClass)
        {
            UE_LOG(LogTemp, Error, TEXT("BulletClass is not set for %s"), *GetName());
        }
    }
#pragma endregion

#pragma region ATTACKS
    void ADRGun::Primary()
    {
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!BulletClass) {
            UE_LOG(LogTemp, Error, TEXT("BulletClass is not set for %s"), *GetName());
            return;
        }

        FVector SpawnLocation = MuzzleComponent->GetComponentLocation();
        FRotator SpawnRotation = MuzzleComponent->GetComponentRotation();

        ADRBullet* NewBullet = GetWorld()->SpawnActor<ADRBullet>(
            BulletClass,
            SpawnLocation,
            SpawnRotation
        );
    }

    void ADRGun::Secondary()
    {
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));
    }

    void ADRGun::Tertiary()
    {
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));
        CurrentMagSize = MaxMagSize;
    }
#pragma endregion
