#include "weapon/gun/DRGun.h"
#include "weapon/gun/DRBullet.h"

#pragma region CORE
    ADRGun::ADRGun()
    {
        MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
        MuzzleLocation->SetupAttachment(WeaponMesh);   
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
        if (!BulletClass) return;

        if (CurrentMagSize < 1) return;

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        GetWorld()->SpawnActor<ADRBullet>(
            BulletClass,
            MuzzleLocation->GetComponentLocation(),
            MuzzleLocation->GetComponentRotation(),
            SpawnParams
        );

        CurrentMagSize--;
    }

    void ADRGun::Secondary()
    {
        
    }

    void ADRGun::Tertiary()
    {
        CurrentMagSize = MaxMagSize;
        UE_LOG(LogTemp, Warning, TEXT("Reloading %s"), *GetName());
    }
#pragma endregion
