// Shoot Them Up Game, All Rights Reserved.

#include "Menu/UI/STUMenuHUD.h"
#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!MenuWidgetClass) return;

    USTUBaseWidget* const MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass);
    if (!MenuWidget) return;
    
    MenuWidget->AddToViewport();
    MenuWidget->Show();
}