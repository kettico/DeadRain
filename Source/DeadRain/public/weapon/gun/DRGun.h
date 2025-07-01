#pragma once

#include "CoreMinimal.h"
#include "weapon/DRWeapon.h"
#include "DRGun.generated.h"

class ADRBullet;

UCLASS()
class DEADRAIN_API ADRGun : public ADRWeapon
{
    GENERATED_BODY()

#pragma region CORE
    public:    
        ADRGun();

    protected:
        virtual void BeginPlay() override;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        USceneComponent* MuzzleLocation; 

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        TSubclassOf<ADRBullet> BulletClass;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        int MaxMagSize = 30;
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        int CurrentMagSize = 30;
        

#pragma endregion

#pragma region ATTACKS
    public:
        virtual void Primary() override;
        virtual void Secondary() override;
        virtual void Tertiary() override; 
#pragma endregion
    
};