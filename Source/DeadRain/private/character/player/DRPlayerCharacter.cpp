#include "character/player/DRPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "interaction/DRInteractableActor.h"
#include "character/player/DRPlayerState.h"
#include "character/player/DRPlayerController.h"

#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"

#include "ui/character/DRHUDWidget.h"
#include "GAS/DRGameplayAbility.h"

#pragma region CORE
    ADRPlayerCharacter::ADRPlayerCharacter(){
        SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
        SpringArm->SetupAttachment(RootComponent);

        Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
        Camera->SetupAttachment(SpringArm);
    }
    void ADRPlayerCharacter::Tick(float DeltaTime){
        Super::Tick(DeltaTime);

        TickInteractionCheck();
    }

    void ADRPlayerCharacter::BeginPlay(){
        Super::BeginPlay();
    }

    void ADRPlayerCharacter::PossessedBy(AController* NewController) {
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));

        Super::PossessedBy(NewController);

        InitializeGAS();
    }

    void ADRPlayerCharacter::OnRep_PlayerState(){
        Super::OnRep_PlayerState();

        InitializeGAS();
    }

#pragma endregion

#pragma region INTERACTION

    void ADRPlayerCharacter::TickInteractionCheck(){


        FVector Start = Camera->GetComponentLocation();
        FVector End = Start + Camera->GetForwardVector() * InteractionDistance;

        FHitResult HitResult;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this); // Ignore self

        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            Start,
            End,
            ECC_Visibility,
            Params
        );

        /*
        DrawDebugLine(
            GetWorld(),
            Start,
            End,
            bHit ? FColor::Green : FColor::Red, // green if hit, red if not
            false,      // don't persist (set true to keep it on screen)
            0.1f,       // duration in seconds (short if called every tick)
            0,          // depth priority
            1.5f        // line thickness
        );
        */

        ADRInteractableActor* NewInteractable = nullptr;
        if (bHit) {
            if (ADRInteractableActor* Interactable = Cast<ADRInteractableActor>(HitResult.GetActor())) {
                if (Interactable->IsInteractable()) {
                    NewInteractable = Interactable;
                }
            }
        }


        if (NewInteractable != CurrentInteractable) {
            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetController())) {
                if (UDRHUDWidget* HUD = PC->GetHUD()) {
                    HUD->SetCurrentInteractable(NewInteractable);
                }
            }
            CurrentInteractable = NewInteractable;
        }
    }

    void ADRPlayerCharacter::InitializeGAS(){
        
        if (ADRPlayerState* PS = GetPlayerState<ADRPlayerState>()){
            AbilitySystemComponent = Cast<UDRAbilitySystemComponent>(PS->GetAbilitySystemComponent());
            PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
            CharacterSet = PS->GetCharacterSet();

            // startup attributes & effects
            Super::InitializeGAS();

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetController())) {
                
            }

            // Initialize Abilities if Preset in Character
            for (int32 i = 0; i < AbilitySlots.Num(); ++i)
            {
                if (AbilitySlots[i])
                {
                    FGameplayAbilitySpec Spec(AbilitySlots[i], 1, i); // Index = InputID
                    FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(Spec);
                    AbilityHandles.Add(Handle);
                }
            }
        }
    }

    void ADRPlayerCharacter::Die() {
       Super::Die();
    }

        #pragma region ATTRIBUTES
        void ADRPlayerCharacter::CurrentHealthChanged(const FOnAttributeChangeData& Data){
            Super::CurrentHealthChanged(Data);

            float CurrentHealth = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetCurrentHealth(CurrentHealth);
                }
            }
        }

        
        void ADRPlayerCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data){
            Super::MaxHealthChanged(Data);
            
            float MaxHealth = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetMaxHealth(MaxHealth);
                }
            }
        }


        void ADRPlayerCharacter::HealthRegenChanged(const FOnAttributeChangeData& Data){
            Super::HealthRegenChanged(Data);
        }

        // Stamina
                void ADRPlayerCharacter::CurrentStaminaChanged(const FOnAttributeChangeData& Data){
            Super::CurrentStaminaChanged(Data);

            float CurrentStamina = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetCurrentStamina(CurrentStamina);
                }
            }
        }

        
        void ADRPlayerCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data){
            Super::MaxStaminaChanged(Data);
            
            float MaxStamina = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetMaxStamina(MaxStamina);
                }
            }
        }


        void ADRPlayerCharacter::StaminaRegenChanged(const FOnAttributeChangeData& Data){
            Super::StaminaRegenChanged(Data);
        }

        // MANA
                void ADRPlayerCharacter::CurrentManaChanged(const FOnAttributeChangeData& Data){
            Super::CurrentManaChanged(Data);

            float CurrentMana = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetCurrentMana(CurrentMana);
                }
            }
        }

        
        void ADRPlayerCharacter::MaxManaChanged(const FOnAttributeChangeData& Data){
            Super::MaxManaChanged(Data);
            
            float MaxMana = Data.NewValue;

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetOwner())){
                if (UDRHUDWidget* HUD = PC->GetHUD()){
                    HUD->SetMaxMana(MaxMana);
                }
            }
        }


        void ADRPlayerCharacter::ManaRegenChanged(const FOnAttributeChangeData& Data){
            Super::ManaRegenChanged(Data);
        }

    #pragma endregion

    #pragma region ABILITIES
    void ADRPlayerCharacter::ActivateAbilityByIndex(int32 Index){
        if (AbilityHandles.IsValidIndex(Index) && AbilityHandles[Index].IsValid())
        {
            AbilitySystemComponent->TryActivateAbility(AbilityHandles[Index]);
        }
    }
    #pragma endregion
#pragma endregion