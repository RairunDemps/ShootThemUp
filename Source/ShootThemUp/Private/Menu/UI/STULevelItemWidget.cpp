// Shoot Them Up Game. All Rights Reserved

#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTULevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (SelectLevelButton)
    {
        SelectLevelButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnSelectLevelButtonClicked);
        SelectLevelButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::OnSelectLevelButtonHovered);
        SelectLevelButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::OnSelectLevelButtonUnhovered);
    }
}

void USTULevelItemWidget::OnSelectLevelButtonClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void USTULevelItemWidget::SetSelected(bool IsSelected)
{
    LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
}

void USTULevelItemWidget::OnSelectLevelButtonHovered()
{
    FrameImage->SetVisibility(ESlateVisibility::Visible);
}

void USTULevelItemWidget::OnSelectLevelButtonUnhovered()
{
    FrameImage->SetVisibility(ESlateVisibility::Hidden);
}
