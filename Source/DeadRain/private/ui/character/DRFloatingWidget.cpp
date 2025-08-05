#include "ui/character/DRFloatingWidget.h"
#include "gas/DRAbilitySystemComponent.h"
#include "gas/attribute/DRCharacterSet.h"

void UDRFloatingWidget::SetAbilitySystemComponent(UDRAbilitySystemComponent* asc){
    if (!asc) return;
    ASC = asc;
    if (!ASC.IsValid()) return;

    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetCurrentHealthAttribute()).AddUObject(this, &UDRFloatingWidget::OnCurrentHealthChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UDRCharacterSet::GetMaxHealthAttribute()).AddUObject(this, &UDRFloatingWidget::OnMaxHealthChanged);

    // Manually Call to Initialize Values
    FOnAttributeChangeData Data;

    Data.Attribute = UDRCharacterSet::GetCurrentHealthAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetCurrentHealthAttribute());
    OnCurrentHealthChanged(Data);

    Data.Attribute = UDRCharacterSet::GetMaxHealthAttribute();
    Data.NewValue = ASC->GetNumericAttribute(UDRCharacterSet::GetMaxHealthAttribute());
    OnMaxHealthChanged(Data);

}

void UDRFloatingWidget::OnCurrentHealthChanged(const FOnAttributeChangeData&  Data){
    CurrentHealth = Data.NewValue;
    CurrentHealthPercent = CurrentHealth / MaxHealth;
}
void UDRFloatingWidget::OnMaxHealthChanged(const FOnAttributeChangeData&  Data){
    MaxHealth = Data.NewValue;
    CurrentHealthPercent = CurrentHealth / MaxHealth;
}