#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRInteractionInterface.h"
#include "DRInteractableActor.generated.h"

class ADRBaseCharacter;
class UDRInteractionPrompt;
UCLASS()
class DEADRAIN_API ADRInteractableActor : public AActor, public IDRInteractionInterface
{
    GENERATED_BODY()

#pragma region CORE
    public:
        ADRInteractableActor();
        

    protected:
        virtual void BeginPlay() override;
        
#pragma endregion

#pragma region INTERFACE
    public:
        virtual void InteractPress_Implementation(ADRBaseCharacter* Interactor) override;
        virtual void InteractHold_Implementation(ADRBaseCharacter* Interactor) override;
        
        virtual bool IsInteractable() const override {return bIsInteractable;}
        virtual void ShowInteractionPrompt(APlayerController* PlayerController, bool Show) override;
    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        bool bIsInteractable = true;

    public:
        UFUNCTION(BlueprintCallable, Category = "Interaction")
        int64 GetCost() const { return Cost; }
    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        int64 Cost = 0;
#pragma endregion
};