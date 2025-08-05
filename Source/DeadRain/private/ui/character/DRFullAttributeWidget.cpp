#include "ui/character/DRFullAttributeWidget.h"
#include "components/ProgressBar.h"
#include "gas/DRAbilitySystemComponent.h"
#include "gas/attribute/DRCharacterSet.h"


void UDRFullAttributeWidget::NativeConstruct(){
    Super::NativeConstruct();
}



void UDRFullAttributeWidget::SetAbilitySystemComponent(UDRAbilitySystemComponent* asc){
    if (!asc) return;
    ASC = asc;
    if (!ASC.IsValid()) return;

    // Bind Attrubyte change Delegates
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentHealthAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnCurrentHealthChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxHealthAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnMaxHealthChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetHealthRegenAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnHealthRegenChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentStaminaAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnCurrentStaminaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxStaminaAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnMaxStaminaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetStaminaRegenAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnStaminaRegenChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentManaAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnCurrentManaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxManaAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnMaxManaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetManaRegenAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnManaRegenChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentMoneyAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnCurrentMoneyChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetAbilityHasteAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnAbilityHasteChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetAttackSpeedAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnAttackSpeedChanged);

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMoveSpeedAttribute()).AddUObject(this, &UDRFullAttributeWidget::OnMoveSpeedChanged);
    
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

    // Money
    Data.Attribute = UDRCharacterSet::GetCurrentMoneyAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetCurrentMoneyAttribute());
    OnCurrentMoneyChanged(Data);

    // Ability Haste
    Data.Attribute = UDRCharacterSet::GetAbilityHasteAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetAbilityHasteAttribute());
    OnAbilityHasteChanged(Data);

    // Attack Speed
    Data.Attribute = UDRCharacterSet::GetAttackSpeedAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetAttackSpeedAttribute());
    OnAttackSpeedChanged(Data);

    // Move Speed
    Data.Attribute = UDRCharacterSet::GetMoveSpeedAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetMoveSpeedAttribute());
    OnMoveSpeedChanged(Data);

}




#pragma region Attributes
    #pragma region Stamina
        void UDRFullAttributeWidget::OnCurrentHealthChanged(const FOnAttributeChangeData&  Data){
            CurrentHealth = Data.NewValue;
        }
        void UDRFullAttributeWidget::OnMaxHealthChanged(const FOnAttributeChangeData&  Data){
            MaxHealth = Data.NewValue;
        }
        void UDRFullAttributeWidget::OnHealthRegenChanged(const FOnAttributeChangeData&  Data){
            HealthRegen = Data.NewValue;
        }
    #pragma endregion

    #pragma region Stamina
        void UDRFullAttributeWidget::OnCurrentStaminaChanged(const FOnAttributeChangeData&  Data){
            CurrentStamina = Data.NewValue;
        }
        void UDRFullAttributeWidget::OnMaxStaminaChanged(const FOnAttributeChangeData&  Data){
            MaxStamina = Data.NewValue;
        }
        void UDRFullAttributeWidget::OnStaminaRegenChanged(const FOnAttributeChangeData&  Data){
            StaminaRegen = Data.NewValue;
        }
    #pragma endregion

    #pragma region Mana
        void UDRFullAttributeWidget::OnCurrentManaChanged(const FOnAttributeChangeData&  Data){
            CurrentMana = Data.NewValue;
        }
        void UDRFullAttributeWidget::OnMaxManaChanged(const FOnAttributeChangeData&  Data){
            MaxMana = Data.NewValue;
        }
        void UDRFullAttributeWidget::OnManaRegenChanged(const FOnAttributeChangeData&  Data){
            ManaRegen = Data.NewValue;
        }
    #pragma endregion

    #pragma region Money
        void UDRFullAttributeWidget::OnCurrentMoneyChanged(const FOnAttributeChangeData&  Data){
            CurrentMoney = Data.NewValue;
        }
    #pragma endregion

    #pragma region Abilities
        void UDRFullAttributeWidget::OnAbilityHasteChanged(const FOnAttributeChangeData&  Data){
            AbilityHaste = Data.NewValue;
        }
    #pragma endregion 

    #pragma region Weapon
        void UDRFullAttributeWidget::OnAttackSpeedChanged(const FOnAttributeChangeData&  Data){
            AttackSpeed = Data.NewValue;
        }
    #pragma endregion 

    #pragma region Movement
        void UDRFullAttributeWidget::OnMoveSpeedChanged(const FOnAttributeChangeData&  Data){
            MoveSpeed = Data.NewValue;
        }

    #pragma endregion 
#pragma endregion