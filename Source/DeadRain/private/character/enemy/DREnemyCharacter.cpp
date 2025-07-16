#include "character/enemy/DREnemyCharacter.h"
#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"
#include "ui/character/DRFloatingWidget.h"

ADREnemyCharacter::ADREnemyCharacter(){
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UDRAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    CharacterSet = CreateDefaultSubobject<UDRCharacterSet>(TEXT("CharacterSet"));

    SetNetUpdateFrequency(100.0f);
}

void ADREnemyCharacter::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
}


void ADREnemyCharacter::OnConstruction(const FTransform& Transform){
    Super::OnConstruction(Transform);

    
}


void ADREnemyCharacter::BeginPlay(){
    Super::BeginPlay();

    InitializeGAS();

    if (FloatingWidget && CharacterSet){
        FloatingWidget->SetCurrentHealth(CharacterSet->GetCurrentHealth());
        FloatingWidget->SetMaxHealth(CharacterSet->GetMaxHealth());
    }

}




void ADREnemyCharacter::InitializeGAS() {
    if (GetLocalRole() != ROLE_Authority)
        return;

    // Only configure or initialize here, do not create subobjects
    if (AbilitySystemComponent && CharacterSet) {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        Super::InitializeGAS();
    }
}
