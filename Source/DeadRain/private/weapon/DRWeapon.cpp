#include "weapon/DRWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "character/DRBaseCharacter.h"

#pragma region CORE
    ADRWeapon::ADRWeapon(){
        WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
        WeaponMesh->SetupAttachment(RootComponent);
    }

    void ADRWeapon::BeginPlay(){
        Super::BeginPlay();
    }
    
#pragma endregion


void ADRWeapon::InteractPress_Implementation(ADRBaseCharacter* Interactor){
    UE_LOG(LogTemp, Warning, TEXT("Weapon Interact Pressed by %s"), *Interactor->GetName());
}

void ADRWeapon::InteractHold_Implementation(ADRBaseCharacter* Interactor){
    UE_LOG(LogTemp, Warning, TEXT("Weapon Interact Held by %s"), *Interactor->GetName());
}

#pragma region ATTACKS
    void ADRWeapon::Primary(){
        //
    }

    void ADRWeapon::Secondary(){

    }

    void ADRWeapon::Tertiary(){
        
    }
#pragma endregion
