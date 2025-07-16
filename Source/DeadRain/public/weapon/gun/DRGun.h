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


        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        USceneComponent* MuzzleComponent; 

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        TSubclassOf<ADRBullet> BulletClass;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        int MaxMagSize = 30;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        int CurrentMagSize = 30;
        

#pragma endregion

#pragma region ATTACKS
    public:
        virtual void Primary() override;
        virtual void Secondary() override;
        virtual void Tertiary() override; 
    protected:
#pragma endregion
    
};