#include "ui/character/DRHUDWidget.h"
#include "ui/character/DRAttributeWidget.h"

#include "interaction/DRInteractableActor.h"



void UDRHUDWidget::SetCurrentHealth(float NewValue){
    if (AttributeWidget) 
        AttributeWidget->SetCurrentHealth(NewValue);  
}

void UDRHUDWidget::SetMaxHealth(float NewValue){
    if (AttributeWidget) 
        AttributeWidget->SetMaxHealth(NewValue);  
}


void UDRHUDWidget::SetCurrentStamina(float NewValue){
    if (AttributeWidget) 
        AttributeWidget->SetCurrentStamina(NewValue);  
}

void UDRHUDWidget::SetMaxStamina(float NewValue){
    if (AttributeWidget) 
        AttributeWidget->SetMaxStamina(NewValue);  
}

void UDRHUDWidget::SetCurrentMana(float NewValue){
    if (AttributeWidget) 
        AttributeWidget->SetCurrentMana(NewValue);  
}

void UDRHUDWidget::SetMaxMana(float NewValue){
    if (AttributeWidget) 
        AttributeWidget->SetMaxMana(NewValue);  
}