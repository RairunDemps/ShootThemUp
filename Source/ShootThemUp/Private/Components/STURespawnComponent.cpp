// Shoot Them Up Game. All Rights Reserved
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogRespawnComponent, All, All)

USTURespawnComponent::USTURespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld()) return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool USTURespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
        ASTUGameModeBase* const GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
        if (!GameMode) return;

        GameMode->RespawnRequest(GetOwner<AController>());
    }
}
