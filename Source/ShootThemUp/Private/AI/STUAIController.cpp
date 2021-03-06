// Shoot Them Up Game. All Rights Reserved

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "Components/STURespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTUAIController::ASTUAIController()
{
    STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
    SetPerceptionComponent(*STUAIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
    bWantsPlayerState = true;
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ASTUAICharacter* const STUCharacter = Cast<ASTUAICharacter>(InPawn);
    if (!STUCharacter) return;

    RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
}

void ASTUAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* const AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASTUAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
