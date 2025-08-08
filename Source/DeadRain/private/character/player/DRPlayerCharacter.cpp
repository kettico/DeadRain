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

#pragma endregion
#pragma region "GAS"
    void ADRPlayerCharacter::InitializeGAS(){
        
        if (ADRPlayerState* PS = GetPlayerState<ADRPlayerState>()){
            AbilitySystemComponent = Cast<UDRAbilitySystemComponent>(PS->GetAbilitySystemComponent());
            PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
            CharacterSet = PS->GetCharacterSet();

            // startup attributes & effects
            Super::InitializeGAS();

            if (ADRPlayerController* PC = Cast<ADRPlayerController>(GetController())) {
                
            }
        }
    }

    void ADRPlayerCharacter::Die() {
       Super::Die();
    }

    #pragma region ATTRIBUTES
            #pragma region HEALTH
                void ADRPlayerCharacter::CurrentHealthChanged(const FOnAttributeChangeData& Data){
                    Super::CurrentHealthChanged(Data); // Base calls Die()

                }

                void ADRPlayerCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data){
                    Super::MaxHealthChanged(Data);
                }

                void ADRPlayerCharacter::HealthRegenChanged(const FOnAttributeChangeData& Data){
                    Super::HealthRegenChanged(Data);
                }
            #pragma endregion

            #pragma region STAMINA
                void ADRPlayerCharacter::CurrentStaminaChanged(const FOnAttributeChangeData& Data){
                    Super::CurrentStaminaChanged(Data);
                }

                void ADRPlayerCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data){
                    Super::MaxStaminaChanged(Data);
                }

                void ADRPlayerCharacter::StaminaRegenChanged(const FOnAttributeChangeData& Data){
                    Super::StaminaRegenChanged(Data);
                }
            #pragma endregion

            #pragma region MANA
                void ADRPlayerCharacter::CurrentManaChanged(const FOnAttributeChangeData& Data){
                    Super::CurrentManaChanged(Data);
                }
                
                void ADRPlayerCharacter::MaxManaChanged(const FOnAttributeChangeData& Data){
                    Super::MaxManaChanged(Data);
                }

                void ADRPlayerCharacter::ManaRegenChanged(const FOnAttributeChangeData& Data){
                    Super::ManaRegenChanged(Data);
                }
            #pragma endregion
    #pragma endregion

    #pragma region ABILITIES



    #pragma endregion
#pragma endregion