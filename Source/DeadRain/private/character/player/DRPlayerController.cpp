#include "character/player/DRPlayerController.h"
#include "ui/character/DRHUDWidget.h"
#include "character/player/DRPlayerState.h"

#pragma region CORE
    ADRPlayerController::ADRPlayerController(){

    }
    
    void ADRPlayerController::Tick(float DeltaTime){
        Super::Tick(DeltaTime);
    }

    void ADRPlayerController::BeginPlay(){
        Super::BeginPlay();
    }

    void ADRPlayerController::OnPossess(APawn* InPawn) {
        Super::OnPossess(InPawn);

        InitializeHUD();
    }

    void ADRPlayerController::OnRep_PlayerState(){
         Super::OnRep_PlayerState();

         InitializeHUD();
    }
        
#pragma endregion


#pragma region - UI
    void ADRPlayerController::InitializeHUD(){
        UE_LOG(LogTemp, Log, TEXT("[%s]"), TEXT(__FUNCTION__));
        
        if (!HUDClass && !HUD){
            UE_LOG(LogTemp, Warning, TEXT("[%s()] - MISSING HUDClass"), *FString(__FUNCTION__));
            return;
        }

        if (!IsLocalPlayerController())
            return;

        if (!HUD)
            HUD = CreateWidget<UDRHUDWidget>(this, HUDClass);

        
        if(HUD){
            HUD->AddToViewport();

            if (ADRPlayerState* PS = GetPlayerState<ADRPlayerState>()){
                HUD->SetCurrentHealth(PS->GetCurrentHealth());
                HUD->SetMaxHealth(PS->GetMaxHealth());
                HUD->SetCurrentMoney(PS->GetCurrentMoney());
            }
        }
    }

    UDRHUDWidget* ADRPlayerController::GetHUD() const{
        return HUD;
    }

#pragma endregion