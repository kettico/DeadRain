#include "character/DRBaseCharacter.h"
#include "weapon/DRWeapon.h"
#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "ui/character/DRFloatingWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

#pragma region CORE
    ADRBaseCharacter::ADRBaseCharacter()
    {
        FloatingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatingWidgetComponent"));
        FloatingWidgetComponent->SetupAttachment(GetMesh());
        FloatingWidgetComponent->SetRelativeLocation(FVector(0, 0, 120));
        FloatingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
        FloatingWidgetComponent->SetDrawSize(FVector2D(500, 500));
    }


    void ADRBaseCharacter::OnConstruction(const FTransform& Transform){
        Super::OnConstruction(Transform);
        

    }
    
    void ADRBaseCharacter::BeginPlay(){
        Super::BeginPlay();

        // Initialize UI
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PC && PC->IsLocalPlayerController()){
            if (FloatingWidgetClass){
                FloatingWidget = CreateWidget<UDRFloatingWidget>(PC, FloatingWidgetClass);
                FloatingWidgetComponent->SetWidget(FloatingWidget);
                if (FloatingWidget){
                    //FloatingWidget->SetOwningCharacter(this);
                    FloatingWidget->SetVisibility(ESlateVisibility::Visible);
                } else {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to create FloatingWidget for %s"), *GetName());
                }
            }
        }

    }

    void ADRBaseCharacter::Tick(float DeltaTime){
        Super::Tick(DeltaTime);
    }
#pragma endregion

#pragma region WEAPON
    void ADRBaseCharacter::EquipWeapon(ADRWeapon* NewWeapon){
        if (!NewWeapon) return;
        if (CurrentWeapon) UnEquipWeapon();

        if (UStaticMeshComponent* WeaponMesh = NewWeapon->GetWeaponMesh()){
            WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            WeaponMesh->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r_socket"));
        }

        CurrentWeapon = NewWeapon;
    }

    void ADRBaseCharacter::UnEquipWeapon(){
        if (CurrentWeapon) return;
    }


    void ADRBaseCharacter::ActivateWeaponPrimary(){
        if (!CurrentWeapon) return;
        CurrentWeapon->Primary();
    }
    void ADRBaseCharacter::ActivateWeaponSecondary(){
        if (!CurrentWeapon) return;
        CurrentWeapon->Secondary();
    }
    void ADRBaseCharacter::ActivateWeaponTertiary(){
        if (!CurrentWeapon) return;
        CurrentWeapon->Tertiary();
    }



#pragma endregion

#pragma region GAS

UAbilitySystemComponent* ADRBaseCharacter::GetAbilitySystemComponent() const{
    return AbilitySystemComponent;
}

float ADRBaseCharacter::GetCurrentHealth() const{
    if (CharacterSet) {
        return CharacterSet->GetCurrentHealth(); // or CharacterSet.Get()->GetCurrentHealth();
    }
    return -1.0f; // Return -1 if not valid
}

void ADRBaseCharacter::InitializeGAS(){
    if(GetLocalRole() != ROLE_Authority || !AbilitySystemComponent)
        return;

    // Add Startup Attributes
    if (!StartupAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}
	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(StartupAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
        
    // Add Startup Effects
	EffectContext.AddSourceObject(this);
	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}


}



#pragma endregion