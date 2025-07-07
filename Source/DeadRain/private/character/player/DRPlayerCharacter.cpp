#include "character/player/DRPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "interaction/DRInteractableActor.h"
#include "character/player/DRPlayerState.h"
#include "character/player/DRPlayerController.h"

#include "gas/attribute/DRCharacterSet.h"
#include "gas/DRAbilitySystemComponent.h"

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

        if (bHit){
            if (ADRInteractableActor* Interactable = Cast<ADRInteractableActor>(HitResult.GetActor())){
                if (Interactable->IsInteractable()){
                    CurrentInteractable = Interactable;
                }
            }
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
        }
    }
#pragma endregion