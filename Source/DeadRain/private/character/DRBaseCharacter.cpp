#include "character/DRBaseCharacter.h"
#include "weapon/DRWeapon.h"
#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "ui/character/DRFloatingWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "gas/DRGameplayAbility.h"

#pragma region CORE
    ADRBaseCharacter::ADRBaseCharacter()
    {
        FloatingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatingWidgetComponent"));
        FloatingWidgetComponent->SetupAttachment(GetMesh());
        
        FloatingWidgetComponent->SetRelativeLocation(FVector(0, 0, 120));
        FloatingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
        FloatingWidgetComponent->SetDrawSize(FVector2D(200, 100));
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
                    FloatingWidget->SetDisplayName(DisplayName);
                } else {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to create FloatingWidget for %s"), *GetName());
                }
            }
        }

        if (AbilitySystemComponent){
            CurrentHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetCurrentHealthAttribute()).AddUObject(this, &ADRBaseCharacter::CurrentHealthChanged);
            MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetMaxHealthAttribute()).AddUObject(this, &ADRBaseCharacter::MaxHealthChanged);
            HealthRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetHealthRegenAttribute()).AddUObject(this, &ADRBaseCharacter::HealthRegenChanged);
         
            CurrentStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetCurrentStaminaAttribute()).AddUObject(this, &ADRBaseCharacter::CurrentStaminaChanged);
            MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetMaxStaminaAttribute()).AddUObject(this, &ADRBaseCharacter::MaxStaminaChanged);
            StaminaRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetStaminaRegenAttribute()).AddUObject(this, &ADRBaseCharacter::StaminaRegenChanged);
            

            CurrentManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetCurrentManaAttribute()).AddUObject(this, &ADRBaseCharacter::CurrentManaChanged);
            MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetMaxManaAttribute()).AddUObject(this, &ADRBaseCharacter::MaxManaChanged);
            ManaRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetManaRegenAttribute()).AddUObject(this, &ADRBaseCharacter::ManaRegenChanged);
            
        }
        

    }
    

    

    void ADRBaseCharacter::Tick(float DeltaTime){
        Super::Tick(DeltaTime);
    }
#pragma endregion

#pragma region WEAPON
    void ADRBaseCharacter::EquipWeapon(ADRWeapon* NewWeapon){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!NewWeapon) return;
        if (CurrentWeapon) UnEquipWeapon();

        if (UStaticMeshComponent* WeaponMesh = NewWeapon->GetWeaponMesh()) {
            WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            WeaponMesh->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r_socket"));
            WeaponMesh->IgnoreActorWhenMoving(this, true);
        }
            
        NewWeapon->SetOwner(this);
        CurrentWeapon = NewWeapon;
    }

    void ADRBaseCharacter::UnEquipWeapon(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (CurrentWeapon) return;
    }


    void ADRBaseCharacter::ActivateWeaponPrimary(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!CurrentWeapon) return;
        CurrentWeapon->Primary();
    }
    void ADRBaseCharacter::ActivateWeaponSecondary(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!CurrentWeapon) return;
        CurrentWeapon->Secondary();
    }
    void ADRBaseCharacter::ActivateWeaponTertiary(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

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
        return CharacterSet->GetCurrentHealth(); 
    }
    return -1.0f;
}

float ADRBaseCharacter::GetCurrentStamina() const{
    if (CharacterSet) {
        return CharacterSet->GetCurrentStamina(); 
    }
    return -1.0f;
}

float ADRBaseCharacter::GetCurrentMana() const{
    if (CharacterSet) {
        return CharacterSet->GetCurrentMana(); 
    }
    return -1.0f;
}



void ADRBaseCharacter::InitializeGAS(){
    UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());
    
    if (!AbilitySystemComponent)
        return;
    /*
    if(GetLocalRole() != ROLE_Authority)
        return;
    */

    // Add Startup Attributes
    if (!StartupAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	} else {
        ApplyGameplayEffectToSelf(StartupAttributes);
    }
        
    // Add Startup Effects
	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		ApplyGameplayEffectToSelf(GameplayEffect);
	}

    // Add Startup Abilities
    for (TSubclassOf<UDRGameplayAbility> Ability :  StartupAbilities){
        AddAbilityToSelf(Ability);
    }


}

    void ADRBaseCharacter::ApplyGameplayEffectToTarget(
        TSubclassOf<UGameplayEffect> GameplayEffectClass,
        ADRBaseCharacter* TargetCharacter
    ){
        if (!AbilitySystemComponent || !TargetCharacter || !GameplayEffectClass) return;
        UE_LOG(LogTemp, Log, TEXT("[%s] - %s applying effect on %s"), TEXT(__FUNCTION__), *GetName(), *TargetCharacter->GetName());
    
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContext);
        if (NewHandle.IsValid())
        {
            FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), TargetCharacter->GetAbilitySystemComponent());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create GameplayEffectSpec for %s"), *GameplayEffectClass->GetName());
        }
        
        
    }

    void ADRBaseCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass){
        if (!AbilitySystemComponent || !GameplayEffectClass) return;
        UE_LOG(LogTemp, Log, TEXT("[%s] - %s applying effect on self"), TEXT(__FUNCTION__), *GetName());

        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContext);
        if (NewHandle.IsValid())
        {
            FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create GameplayEffectSpec for %s"), *GameplayEffectClass->GetName());
        }
    }

    bool ADRBaseCharacter::AddAbilityToSelf(TSubclassOf<UDRGameplayAbility> NewAbilityClass){
        if (!AbilitySystemComponent || !NewAbilityClass) return false;
        UE_LOG(LogTemp, Log, TEXT("[%s] - %s Adding Ability on self"), TEXT(__FUNCTION__), *GetName());

        
        FGameplayAbilitySpec Spec(static_cast<TSubclassOf<UGameplayAbility>>(NewAbilityClass), 1, INDEX_NONE, this);

        AbilitySystemComponent->GiveAbility(Spec);

        return true;
    }

    bool ADRBaseCharacter::AddAbilityToTarget(TSubclassOf<UDRGameplayAbility> NewAbilityClass, ADRBaseCharacter* TargetCharacter){
        if (!AbilitySystemComponent || !TargetCharacter || !NewAbilityClass) return false;
        UE_LOG(LogTemp, Log, TEXT("[%s] - %s Adding Ability on %s"), TEXT(__FUNCTION__), *GetName(), *TargetCharacter->GetName());

        
        UAbilitySystemComponent* TargetASC = TargetCharacter->GetAbilitySystemComponent();
        if (!TargetASC || !HasAuthority())
            return false;

        UE_LOG(LogTemp, Log, TEXT("[%s] - %s Adding Ability on %s"), TEXT(__FUNCTION__), *GetName(), *TargetCharacter->GetName());

        FGameplayAbilitySpec Spec(static_cast<TSubclassOf<UGameplayAbility>>(NewAbilityClass), 1, INDEX_NONE, this);

        TargetASC->GiveAbility(Spec);

        return true;
    }



    void ADRBaseCharacter::Die() {
        UE_LOG(LogTemp, Error, TEXT("%s Died "), *GetName());
    }


    #pragma region ATTRIBUTES
        void ADRBaseCharacter::CurrentHealthChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());
            
            float CurrentHealth = Data.NewValue;

            if (FloatingWidget){
                FloatingWidget->SetCurrentHealth(CurrentHealth);
            }
        }

        
        void ADRBaseCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());

            float MaxHealth = Data.NewValue;

            if (FloatingWidget){
                FloatingWidget->SetMaxHealth(MaxHealth);
            }
        }


        void ADRBaseCharacter::HealthRegenChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());


        }

        // STAMINA
                void ADRBaseCharacter::CurrentStaminaChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());
            
            float CurrentStamina = Data.NewValue;

        }

        
        void ADRBaseCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());

            float MaxStamina = Data.NewValue;

        }


        void ADRBaseCharacter::StaminaRegenChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());


        }

                // Mana
                void ADRBaseCharacter::CurrentManaChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());
            
            float CurrentMana = Data.NewValue;

        }

        
        void ADRBaseCharacter::MaxManaChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());

            float MaxMana = Data.NewValue;


        }


        void ADRBaseCharacter::ManaRegenChanged(const FOnAttributeChangeData& Data){
            UE_LOG(LogTemp, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());


        }

    #pragma endregion


#pragma endregion