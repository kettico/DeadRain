#include "ui/character/DRStatWidget.h"




void UDRStatItem::NativeConstruct() {
    Super::NativeConstruct();


    if (StatNameBlock) {
        StatNameBlock->SetText(StatName);
    }

    if (StatValueBlock) {
        StatValueBlock->SetText(FText::AsNumber(StatValue));
    }
}
  
