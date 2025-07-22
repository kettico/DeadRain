#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ui/components/DRTextBlock.h"
#include "DRStatWidget.generated.h"


/*
* Contain Text and Float of an attribute Value
*/
UCLASS()
class DEADRAIN_API UDRStatItem : public UUserWidget
{
    GENERATED_BODY()

public:
        virtual void NativeConstruct() override;
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
    float StatValue = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
    FText StatName = FText::FromString(TEXT("Default Name"));
    
    UPROPERTY(meta = (BindWidget))
    UDRTextBlock* StatNameBlock;
    UPROPERTY(meta = (BindWidget))
    UDRTextBlock* StatValueBlock;
};

/*
* Holder for all StatItems
*/
UCLASS()
class DEADRAIN_API UDRStatWidget : public UUserWidget
{
    GENERATED_BODY()

public:

protected:
};