// Shoot Them Up Game. All Rights Reserved

#include "UI/STUGameOverWidget.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Controller.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        if (ASTUGameModeBase* const GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
    if (State == ESTUMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USTUGameOverWidget::UpdatePlayersStat()
{
    if (!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();

    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* const Controller = It->Get();
        if (!Controller) continue;

        ASTUPlayerState* const PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
        if (!PlayerState) continue;

        USTUPlayerStatRowWidget* const PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(STUUtils::FromStringToInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(STUUtils::FromStringToInt(PlayerState->GetDeathNum()));
        PlayerStatRowWidget->SetTeam(STUUtils::FromStringToInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndcatorVisibility(Controller->IsPlayerController());
        PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());
        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}

void USTUGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
