#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRFloatingWidget.generated.h"

class ADRBaseCharacter;

UCLASS()
class DEADRAIN_API UDRFloatingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintImplementableEvent, Category = "FloatingWidget")
    void SetCurrentHealth(float NewValue);
    UFUNCTION(BlueprintImplementableEvent, Category = "FloatingWidget")
    void SetMaxHealth(float NewValue);
    UFUNCTION(BlueprintImplementableEvent, Category = "FloatingWidget")
    void SetDisplayName(const FText& Name);
protected:

    


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingWidget")
    float CurrentHealth = 100.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingWidget")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingWidget")
    FText DisplayName = FText::FromString(TEXT("DEFAULT NAME"));

};