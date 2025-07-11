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

        GetWorld()->SpawnActor<ADRBullet>(
            BulletClass,
            MuzzleLocation->GetComponentLocation(),
            MuzzleLocation->GetComponentRotation(),
            SpawnParams
        );

        FVector SpawnLocation = MuzzleLocation->GetComponentLocation();

        UE_LOG(LogTemp, Warning, TEXT("Bullet spawned at %f, %f, %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
        UE_LOG(LogTemp, Warning, TEXT("Character Location: %f, %f, %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

        CurrentMagSize--;
    }

    void ADRGun::Secondary()
    {
        
    }

    void ADRGun::Tertiary()
    {
        CurrentMagSize = MaxMagSize;
    }
#pragma endregion
