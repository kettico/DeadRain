#include "character/player/DRPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "interaction/DRInteractableActor.h"

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

        if (bHit){
            if (ADRInteractableActor* Interactable = Cast<ADRInteractableActor>(HitResult.GetActor())){
                if (Interactable->IsInteractable()){
                    UE_LOG(LogTemp, Warning, TEXT("Hit an interactable actor: %s"), *Interactable->GetName());
                    CurrentInteractable = Interactable;
                }
            }
        }
    }

    void ADRPlayerCharacter::InputInteract() {
        if (CurrentInteractable){
            CurrentInteractable->InteractPress(this);
            UE_LOG(LogTemp, Warning, TEXT("Interacted with: %s"), *CurrentInteractable->GetName());
        }
    }

#pragma endregion