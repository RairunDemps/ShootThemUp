// Shoot Them Up Game, All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "Player/STUPlayerState.h"
#include "Components/ProgressBar.h"

int32 USTUPlayerHUDWidget::GetKillsNum() const
{
    APlayerController* Controller = GetOwningPlayer();
    ASTUPlayerState* PlayerState = Controller->GetPlayerState<ASTUPlayerState>();

    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }

    UpdateHealthBar();
}

void USTUPlayerHUDWidget::UpdateHealthBar()
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData& Data) const
{
    USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(Data);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());

    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    APlayerController* Controller = GetOwningPlayer();

    return Controller && Controller->GetStateName() == NAME_Spectating;
}

FString USTUPlayerHUDWidget::BulletsFromIntToText(int32 BulletsNum) const
{
    int32 MaxLen = 3;
    TCHAR FillSymbol = '0';
    FString BulletsNumStr = FString::FromInt(BulletsNum);
    int NumberOfSymbolsToFill = MaxLen - BulletsNumStr.Len();
    if (NumberOfSymbolsToFill > 0)
    {
        BulletsNumStr = FString::ChrN(NumberOfSymbolsToFill, FillSymbol).Append(BulletsNumStr);
    }

    return BulletsNumStr;
}
