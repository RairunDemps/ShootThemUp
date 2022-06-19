// Shoot Them Up Game. All Rights Reserved

#include "UI/STUGamePauseWidget.h"
#include "Components/Button.h"
#include "STUGameModeBase.h"

void USTUGamePauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUGamePauseWidget::OnClearPause);
    }
}

void USTUGamePauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
