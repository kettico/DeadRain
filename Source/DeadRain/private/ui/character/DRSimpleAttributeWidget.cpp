#include "ui/character/DRSimpleAttributeWidget.h"
#include "components/ProgressBar.h"
#include "gas/DRAbilitySystemComponent.h"
#include "gas/attribute/DRCharacterSet.h"


void UDRSimpleAttributeWidget::NativeConstruct(){
    Super::NativeConstruct();
}



void UDRSimpleAttributeWidget::SetAbilitySystemComponent(UDRAbilitySystemComponent* asc){
    if (!asc) return;
    ASC = asc;
    if (!ASC.IsValid()) return;

    // Bind Attrubyte change Delegates
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentHealthAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnCurrentHealthChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxHealthAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnMaxHealthChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetHealthRegenAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnHealthRegenChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentStaminaAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnCurrentStaminaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxStaminaAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnMaxStaminaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetStaminaRegenAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnStaminaRegenChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentManaAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnCurrentManaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxManaAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnMaxManaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetManaRegenAttribute()).AddUObject(this, &UDRSimpleAttributeWidget::OnManaRegenChanged);

    
    // Manually Call to Initialize Values
    FOnAttributeChangeData Data;

    Data.Attribute = UDRCharacterSet::GetCurrentHealthAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetCurrentHealthAttribute());
    OnCurrentHealthChanged(Data);

    Data.Attribute = UDRCharacterSet::GetMaxHealthAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetMaxHealthAttribute());
    OnMaxHealthChanged(Data);

    Data.Attribute = UDRCharacterSet::GetHealthRegenAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetHealthRegenAttribute());
    OnHealthRegenChanged(Data);

    // Stamina
    Data.Attribute = UDRCharacterSet::GetCurrentStaminaAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetCurrentStaminaAttribute());
    OnCurrentStaminaChanged(Data);

    Data.Attribute = UDRCharacterSet::GetMaxStaminaAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetMaxStaminaAttribute());
    OnMaxStaminaChanged(Data);

    Data.Attribute = UDRCharacterSet::GetStaminaRegenAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetStaminaRegenAttribute());
    OnStaminaRegenChanged(Data);

    // Mana
    Data.Attribute = UDRCharacterSet::GetCurrentManaAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetCurrentManaAttribute());
    OnCurrentManaChanged(Data);

    Data.Attribute = UDRCharacterSet::GetMaxManaAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetMaxManaAttribute());
    OnMaxManaChanged(Data);

    Data.Attribute = UDRCharacterSet::GetManaRegenAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetManaRegenAttribute());
    OnManaRegenChanged(Data);
}



#pragma region Attributes
    #pragma region Stamina
        void UDRSimpleAttributeWidget::OnCurrentHealthChanged(const FOnAttributeChangeData&  Data){
            CurrentHealth = Data.NewValue;
            CurrentHealthPercent = CurrentHealth / MaxHealth;
        }
        void UDRSimpleAttributeWidget::OnMaxHealthChanged(const FOnAttributeChangeData&  Data){
            MaxHealth = Data.NewValue;
            CurrentHealthPercent = CurrentHealth / MaxHealth;
        }
        void UDRSimpleAttributeWidget::OnHealthRegenChanged(const FOnAttributeChangeData&  Data){
            HealthRegen = Data.NewValue;
        }
    #pragma endregion

    #pragma region Stamina
        void UDRSimpleAttributeWidget::OnCurrentStaminaChanged(const FOnAttributeChangeData&  Data){
            CurrentStamina = Data.NewValue;
            CurrentStaminaPercent = CurrentStamina / MaxStamina;
        }
        void UDRSimpleAttributeWidget::OnMaxStaminaChanged(const FOnAttributeChangeData&  Data){
            MaxStamina = Data.NewValue;
            CurrentStaminaPercent = CurrentStamina / MaxStamina;
        }
        void UDRSimpleAttributeWidget::OnStaminaRegenChanged(const FOnAttributeChangeData&  Data){
            StaminaRegen = Data.NewValue;
        }
    #pragma endregion

    #pragma region Mana
        void UDRSimpleAttributeWidget::OnCurrentManaChanged(const FOnAttributeChangeData&  Data){
            CurrentMana = Data.NewValue;
            CurrentManaPercent = CurrentMana / MaxMana;
        }
        void UDRSimpleAttributeWidget::OnMaxManaChanged(const FOnAttributeChangeData&  Data){
            MaxMana = Data.NewValue;
            CurrentManaPercent = CurrentMana / MaxMana;
        }
        void UDRSimpleAttributeWidget::OnManaRegenChanged(const FOnAttributeChangeData&  Data){
            ManaRegen = Data.NewValue;
        }
    #pragma endregion
#pragma endregion