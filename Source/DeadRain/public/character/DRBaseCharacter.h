#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "DRBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UDRAbilitySystemComponent;
class UDRCharacterSet;
class UGameplayEffect;

class UDRItemManager;
class ADRItem;
class ADRWeapon;

class UDRFloatingWidget;
class UWidgetComponent;
UCLASS()
class DEADRAIN_API ADRBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()


#pragma region CORE
    public:
        ADRBaseCharacter();
        virtual void Tick(float DeltaTime) override;

        UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
        virtual FText GetDisplayName() const { return DisplayName; }
        UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
        virtual void SetDisplayName(FText NewName)  { DisplayName = NewName; }


    protected:
        virtual void OnConstruction(const FTransform& Transform) override;
        virtual void BeginPlay() override;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        FText DisplayName = FText::FromString(TEXT("DEFAULT NAME"));
#pragma endregion

#pragma region INTERFACE

    public:

    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")  
        TSubclassOf<UDRFloatingWidget> FloatingWidgetClass;
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")  
        UDRFloatingWidget* FloatingWidget;
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        UWidgetComponent* FloatingWidgetComponent;
#pragma endregion

#pragma region INVENTORY
    public:
    protected:
#pragma endregion    

#pragma region WEAPON
    public:
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void EquipWeapon(ADRWeapon* NewWeapon);
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void UnEquipWeapon();

        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void ActivateWeaponPrimary();
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void ActivateWeaponSecondary();
        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void ActivateWeaponTertiary();

    protected:
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        ADRWeapon* CurrentWeapon;
#pragma endregion

#pragma region GAS

public:
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "GAS|Character|Attributes")
	float GetCurrentHealth() const;

    UFUNCTION(BlueprintCallable, Category = "GAS|Character|Attributes")
    void ApplyGameplayEffectToTarget( TSubclassOf<UGameplayEffect> GameplayEffectClass, ADRBaseCharacter* TargetCharacter);
    UFUNCTION(BlueprintCallable, Category = "GAS|Character|Attributes")
    void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDRAbilitySystemComponent* AbilitySystemComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDRCharacterSet* CharacterSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DEADRAIN|GAS|Startup")
	TSubclassOf<UGameplayEffect> StartupAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DEADRAIN|GAS|Startup")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

    virtual void InitializeGAS();


    FDelegateHandle CurrentHealthChangedDelegateHandle;
    virtual void CurrentHealthChanged(const FOnAttributeChangeData& Data);

    FDelegateHandle MaxHealthChangedDelegateHandle;
    virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
    FDelegateHandle HealthRegenChangedDelegateHandle;
    virtual void HealthRegenChanged(const FOnAttributeChangeData& Data);




#pragma endregion
    
};