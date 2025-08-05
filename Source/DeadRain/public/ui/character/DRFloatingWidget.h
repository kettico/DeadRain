#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRFloatingWidget.generated.h"

class ADRBaseCharacter;
class UDRAbilitySystemComponent;
struct FOnAttributeChangeData;

UCLASS()
class DEADRAIN_API UDRFloatingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetAbilitySystemComponent(UDRAbilitySystemComponent* asc);
    
    UFUNCTION(BlueprintImplementableEvent, Category = "FloatingWidget")
        void SetDisplayName(const FText& Name);
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingWidget")
        FText DisplayName = FText::FromString(TEXT("DEFAULT NAME"));

protected:
    TWeakObjectPtr<UDRAbilitySystemComponent> ASC;


#pragma region Attributes   
    public:
        void OnCurrentHealthChanged(const FOnAttributeChangeData&  Data);
        void OnMaxHealthChanged(const FOnAttributeChangeData&  Data);
    protected:
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentHealth = -1.0f;
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float MaxHealth = -1.0f;
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
            float CurrentHealthPercent = -1.0f;
#pragma endregion
};