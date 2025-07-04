#include "gas/DRAbilitySystemComponent.h"

void UDRAbilitySystemComponent::ReceiveDamage(UDRAbilitySystemComponent * SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}