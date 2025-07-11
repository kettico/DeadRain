#include "weapon/DRWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "character/DRBaseCharacter.h"

#pragma region CORE
    ADRWeapon::ADRWeapon(){
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
        WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
        WeaponMesh->SetupAttachment(RootComponent);
    }

    void ADRWeapon::BeginPlay(){
        Super::BeginPlay();
    }
    
#pragma endregion


void ADRWeapon::InteractPress_Implementation(ADRBaseCharacter* Interactor){
    Interactor->EquipWeapon(this);
}

void ADRWeapon::InteractHold_Implementation(ADRBaseCharacter* Interactor){
    Interactor->EquipWeapon(this);
}

#pragma region ATTACKS
    void ADRWeapon::Primary(){
        UE_LOG(LogTemp, Warning, TEXT("Primary attack executed on %s"), *GetName());
    }

    void ADRWeapon::Secondary(){

    }

    void ADRWeapon::Tertiary(){
        
    }
#pragma endregion
