#include "character/DRBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayEffect.h"

#include "weapon/DRWeapon.h"
#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"
#include "gas/DRGameplayAbility.h"
#include "gas/ability/DRAbilitySlot.h"
#include "ui/character/DRFloatingWidget.h"
#include "interaction/DRItemManagerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogDRBaseCharacter, Log, All);

#pragma region CORE
    ADRBaseCharacter::ADRBaseCharacter()
    {
        FloatingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatingWidgetComponent"));
        FloatingWidgetComponent->SetupAttachment(GetMesh());
        
        FloatingWidgetComponent->SetRelativeLocation(FVector(0, 0, 120));
        FloatingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
        FloatingWidgetComponent->SetDrawSize(FVector2D(200, 100));


        ItemManager = CreateDefaultSubobject<UDRItemManagerComponent>(TEXT("ItemManager"));
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
                    UE_LOG(LogDRBaseCharacter, Warning, TEXT("Failed to create FloatingWidget for %s"), *GetName());
                }
            }
        }

        BindAttributeDelegates();
                

    }
    

    

    void ADRBaseCharacter::Tick(float DeltaTime){
        Super::Tick(DeltaTime);
    }
#pragma endregion

#pragma region WEAPON
    void ADRBaseCharacter::EquipWeapon(ADRWeapon* NewWeapon){
        UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

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

        if (CurrentWeapon) return;
    }


    void ADRBaseCharacter::ActivateWeaponPrimary(){
        UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!CurrentWeapon) return;
        CurrentWeapon->Primary();
    }
    void ADRBaseCharacter::ActivateWeaponSecondary(){
        UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!CurrentWeapon) return;
        CurrentWeapon->Secondary();
    }
    void ADRBaseCharacter::ActivateWeaponTertiary(){
        UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        if (!CurrentWeapon) return;
        CurrentWeapon->Tertiary();
    }



#pragma endregion

#pragma region GAS
    UAbilitySystemComponent* ADRBaseCharacter::GetAbilitySystemComponent() const {
        return AbilitySystemComponent;
    }

void ADRBaseCharacter::BindAttributeDelegates(){
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
        

        MoveSpeedChangedDelegateHandle= AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetMoveSpeedAttribute()).AddUObject(this, &ADRBaseCharacter::MoveSpeedChanged);
        
    }
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
    UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s] - [%s]"), TEXT(__FUNCTION__), *GetName());
    
    if (!AbilitySystemComponent)
        return;
    /*
    if(GetLocalRole() != ROLE_Authority)
        return;
    */

    // Add Startup Attributes
    if (!StartupAttributes)
	{
		UE_LOG(LogDRBaseCharacter, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	} else {
        ApplyGameplayEffectToSelf(StartupAttributes);
    }
        
    // Add Startup Effects
	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		ApplyGameplayEffectToSelf(GameplayEffect);
	}

    AbilitySlots.Empty();
    for( int i = 0; i < 5; i++){
        UDRAbilitySlot* NewSlot = NewObject<UDRAbilitySlot>(this);
        if (NewSlot){
            NewSlot->SetAbilitySystemComponent(AbilitySystemComponent);
            AbilitySlots.Add(NewSlot);
        }
    }


    if (FloatingWidget){
        FloatingWidget->SetAbilitySystemComponent(AbilitySystemComponent);
    }
}

    void ADRBaseCharacter::ApplyGameplayEffectToTarget(
        TSubclassOf<UGameplayEffect> GameplayEffectClass,
        ADRBaseCharacter* TargetCharacter
    ){
        if (!AbilitySystemComponent || !TargetCharacter || !GameplayEffectClass) return;
        UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s] - %s applying effect on %s"), TEXT(__FUNCTION__), *GetName(), *TargetCharacter->GetName());
    
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContext);
        if (NewHandle.IsValid())
        {
            FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), TargetCharacter->GetAbilitySystemComponent());
        }
        else
        {
            UE_LOG(LogDRBaseCharacter, Error, TEXT("Failed to create GameplayEffectSpec for %s"), *GameplayEffectClass->GetName());
        }
        
        
    }

    void ADRBaseCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass){
        if (!AbilitySystemComponent || !GameplayEffectClass) return;
        UE_LOG(LogDRBaseCharacter, Log, TEXT("[%s] - %s applying effect on self"), TEXT(__FUNCTION__), *GetName());

        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContext);
        if (NewHandle.IsValid())
        {
            FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
        }
        else
        {
            UE_LOG(LogDRBaseCharacter, Error, TEXT("Failed to create GameplayEffectSpec for %s"), *GameplayEffectClass->GetName());
        }
    }

        #pragma region "Ability"
            UDRAbilitySlot* ADRBaseCharacter::GetAbilitySlotByIndex(int32 idx) const{
                if (idx < 0 || idx >= AbilitySlots.Num()) return nullptr;

                return AbilitySlots[idx];
            }
        #pragma endregion


    void ADRBaseCharacter::Die() {
        UE_LOG(LogDRBaseCharacter, Error, TEXT("%s Died "), *GetName());
    }

    #pragma region ATTRIBUTES
        #pragma region "HEALTH"
            void ADRBaseCharacter::CurrentHealthChanged(const FOnAttributeChangeData& Data){
                float CurrentHealth = Data.NewValue;

                if (CurrentHealth <= 0.0f){
                    Die();
                }
            }
            void ADRBaseCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data){}
            void ADRBaseCharacter::HealthRegenChanged(const FOnAttributeChangeData& Data){}
        #pragma endregion
        #pragma region "STAMINA"
            void ADRBaseCharacter::CurrentStaminaChanged(const FOnAttributeChangeData& Data){}
            void ADRBaseCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data){}
            void ADRBaseCharacter::StaminaRegenChanged(const FOnAttributeChangeData& Data){}
        #pragma endregion
        #pragma region "MANA"
            void ADRBaseCharacter::CurrentManaChanged(const FOnAttributeChangeData& Data){}
            void ADRBaseCharacter::MaxManaChanged(const FOnAttributeChangeData& Data){}
            void ADRBaseCharacter::ManaRegenChanged(const FOnAttributeChangeData& Data){}
        #pragma endregion
        #pragma region "MOVEMENT"
            void ADRBaseCharacter::MoveSpeedChanged(const FOnAttributeChangeData& Data){
                float NewMoveSpeed = Data.NewValue;
                UE_LOG(LogDRBaseCharacter, Log, TEXT("MoveSpeed changed to %f"), NewMoveSpeed);
                if (GetCharacterMovement()){
                    GetCharacterMovement()->MaxWalkSpeed = NewMoveSpeed;
                }
            }
        #pragma endregion

    #pragma endregion


#pragma endregion