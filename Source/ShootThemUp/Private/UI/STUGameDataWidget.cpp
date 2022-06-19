// Shoot Them Up Game. All Rights Reserved

#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
    const ASTUGameModeBase* GameMode = GetSTUGameMode();

    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const
{
    const ASTUGameModeBase* GameMode = GetSTUGameMode();

    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const
{
    const ASTUGameModeBase* GameMode = GetSTUGameMode();

    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const
{
    return GetWorld() ? GetWorld()->GetAuthGameMode<ASTUGameModeBase>() : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
    return GetOwningPlayer() ? GetOwningPlayer()->GetPlayerState<ASTUPlayerState>() : nullptr;
}
