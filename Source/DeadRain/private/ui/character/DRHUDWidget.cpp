#include "ui/character/DRHUDWidget.h"
#include "interaction/DRInteractableActor.h"
#include "ui/character/DRAbilityBarWidget.h"
#include "ui/character/DRSimpleAttributeWidget.h"
#include "ui/character/DRFullAttributeWidget.h"
#include "gas/DRAbilitySystemComponent.h"



void UDRHUDWidget::NativeConstruct(){
    Super::NativeConstruct();
}

void UDRHUDWidget::SetAbilitySystemComponent(UDRAbilitySystemComponent* asc){
    if (!asc) return;
    ASC = asc;
    if (!ASC.IsValid()) return;

    if (SimpleAttributeWidget) 
        SimpleAttributeWidget->SetAbilitySystemComponent(ASC.Get());
    if (FullAttributeWidget) 
        FullAttributeWidget->SetAbilitySystemComponent(ASC.Get());

    
}



#pragma region ATTRIBUTES
    void UDRHUDWidget::AddAbility(TSubclassOf<UDRGameplayAbility> NewValue){
    if (AbilityBarWidget)
        AbilityBarWidget->AddAbility(NewValue);
    }
    void UDRHUDWidget::RemoveAbility(TSubclassOf<UDRGameplayAbility> NewValue){
        if (AbilityBarWidget)
            AbilityBarWidget->RemoveAbility(NewValue);
    }
#pragma endregion



