#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

class UDRHUDWidget;

UCLASS()
class DEADRAIN_API ADRPlayerController : public APlayerController
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRPlayerController();
        virtual void Tick(float DeltaTime) override;

    protected:
        virtual void BeginPlay() override;

        virtual void OnPossess(APawn* InPawn) override;

	    virtual void OnRep_PlayerState() override;
        
#pragma endregion

#pragma region - UI

public:
    void InitializeHUD();
    UDRHUDWidget* GetHUD() const;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DeadRain|UI")
	TSubclassOf<UDRHUDWidget> HUDClass;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DeadRain|UI")
	UDRHUDWidget* HUD;



protected:

 
#pragma endregion
};