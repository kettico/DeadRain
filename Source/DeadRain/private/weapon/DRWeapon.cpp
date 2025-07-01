#include "weapon/DRWeapon.h"
#include "Components/StaticMeshComponent.h"

#pragma region CORE
    ADRWeapon::ADRWeapon(){
        WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
        WeaponMesh->SetupAttachment(RootComponent);
    }

    void ADRWeapon::BeginPlay(){
        Super::BeginPlay();
    }
    
#pragma endregion

#pragma region ATTACKS
    void ADRWeapon::Primary(){

    }

    void ADRWeapon::Secondary(){

    }

    void ADRWeapon::Tertiary(){
        
    }
#pragma endregion
