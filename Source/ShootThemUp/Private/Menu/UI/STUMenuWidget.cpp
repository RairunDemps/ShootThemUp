// Shoot Them Up Game, All Rights Reserved.

#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STUCoreTypes.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "Components/HorizontalBox.h"
#include "Sound/SoundCue.h"

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }

    InitLevels();
}

void USTUMenuWidget::InitLevels()
{
    USTUGameInstance* const STUGameInstance = GetGameInstance();
    if (!STUGameInstance) return;

    checkf(STUGameInstance->GetLevelsData().Num() != 0, TEXT("Number of levels is zero"));

    if (!LevelItemsBox) return;

    LevelItemsBox->ClearChildren();
    for (const FLevelData& LevelData : STUGameInstance->GetLevelsData())
    {
        USTULevelItemWidget* const LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);
        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(STUGameInstance->GetStartupLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    USTUGameInstance* const STUGameInstance = GetGameInstance();
    if (!STUGameInstance) return;

    STUGameInstance->SetStartupLevel(Data);
    for (USTULevelItemWidget* const LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const bool IsSelected = LevelItemWidget->GetLevelData().LevelName == Data.LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void USTUMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), GameStartSound);
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation == HideAnimation)
    {
        USTUGameInstance* const STUGameInstance = GetGameInstance();
        if (!STUGameInstance) return;

        UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
    }
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USTUGameInstance* USTUMenuWidget::GetGameInstance() const
{
    if (!GetWorld()) return nullptr;

    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
