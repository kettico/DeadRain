#include "character/enemy/DREnemyCharacter.h"
#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"

ADREnemyCharacter::ADREnemyCharacter(){
    PrimaryActorTick.bCanEverTick = true;

    InitializeGAS();
}

void ADREnemyCharacter::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
}




void ADREnemyCharacter::BeginPlay(){
    Super::BeginPlay();

    
}




void ADREnemyCharacter::InitializeGAS(){
    if(GetLocalRole() != ROLE_Authority)
        return;

    AbilitySystemComponent = CreateDefaultSubobject<UDRAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    if(AbilitySystemComponent){
        AbilitySystemComponent->SetIsReplicated(true);
        AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

        CharacterSet = CreateDefaultSubobject<UDRCharacterSet>(TEXT("CharacterSet"));
    }
    
}

/*

LoginId:24f4e2b3405d5538e279c8b36ee079de
EpicAccountId:8e2a0c8505f74be0b6b99804fafc4f9a

Fatal error: [File:D:\build\++UE5\Sync\Engine\Source\Runtime\CoreUObject\Private\UObject\UObjectGlobals.cpp] [Line: 5544] 
Default subobject DRAbilitySystemComponent AbilitySystemComponent already exists for DREnemyCharacter /Script/DeadRain.Default__DREnemyCharacter.




UnrealEditor_CoreUObject
UnrealEditor_CoreUObject
UnrealEditor_DeadRain!ADREnemyCharacter::InitializeGAS() [C:\Users\Kettic\Desktop\DeadRain\Source\DeadRain\private\character\enemy\DREnemyCharacter.cpp:31]
UnrealEditor_DeadRain!ADREnemyCharacter::InitializeGAS() [C:\Users\Kettic\Desktop\DeadRain\Source\DeadRain\private\character\enemy\DREnemyCharacter.cpp:38]
UnrealEditor_DeadRain!ADREnemyCharacter::ADREnemyCharacter() [C:\Users\Kettic\Desktop\DeadRain\Source\DeadRain\private\character\enemy\DREnemyCharacter.cpp:8]
UnrealEditor_CoreUObject
*/