#include "gas/DRAbilityActor.h"
#include "Components/StaticMeshComponent.h"

ADRAbilityActor::ADRAbilityActor()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
    MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    MeshComponent->SetSimulatePhysics(true); // optional for visual bounce
}