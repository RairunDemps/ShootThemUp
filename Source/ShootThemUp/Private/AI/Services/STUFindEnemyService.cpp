// Shoot Them Up Game. All Rights Reserved

#include "AI/Services/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIPerceptionComponent.h"

USTUFindEnemyService::USTUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        AAIController* const Controller = OwnerComp.GetAIOwner();
        USTUAIPerceptionComponent* const PerceptionComponent = STUUtils::GetSTUPlayerComponent<USTUAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
