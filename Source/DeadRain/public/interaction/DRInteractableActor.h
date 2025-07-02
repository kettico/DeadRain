#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRInteractionInterface.h"
#include "DRInteractableActor.generated.h"

class ADRBaseCharacter;

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
        UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void InteractPress(ADRBaseCharacter* Interactor);
        void InteractPress_Implementation(ADRBaseCharacter* Interactor);

        UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void InteractHold(ADRBaseCharacter* Interactor);
        void InteractHold_Implementation(ADRBaseCharacter* Interactor);
        
        virtual bool IsInteractable() const;
        virtual void ShowInteractionPrompt(APlayerController* PlayerController, bool Show);
    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
        bool bIsInteractable = true;

        
#pragma endregion
};