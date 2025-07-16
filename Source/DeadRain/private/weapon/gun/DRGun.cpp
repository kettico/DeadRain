#include "weapon/gun/DRGun.h"
#include "weapon/gun/DRBullet.h"

#pragma region CORE
    ADRGun::ADRGun()
    {
        if (WeaponMesh){
            MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
            MuzzleLocation->SetupAttachment(WeaponMesh);   
        }
        CurrentMagSize = 100;
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

        if (CurrentMagSize < 1) {
            UE_LOG(LogTemp, Warning, TEXT("Out of ammo in %s"), *GetName());
            return;
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Owner = GetOwner();

        GetWorld()->SpawnActor<ADRBullet>(
            BulletClass,
            MuzzleLocation->GetComponentLocation(),
            MuzzleLocation->GetComponentRotation(),
            SpawnParams
        );

        FVector SpawnLocation = MuzzleLocation->GetComponentLocation();

        CurrentMagSize--;
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
