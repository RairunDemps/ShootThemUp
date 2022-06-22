// Shoot Them Up Game. All Rights Reserved

#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* const Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard) return EBTNodeResult::Failed;

    APawn* const Pawn = Controller->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavigationSystem) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    FVector Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        AActor* const CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor) return EBTNodeResult::Failed;

        Location = CenterActor->GetActorLocation();
    }

    const bool Found = NavigationSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation);
    if (!Found) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

    return EBTNodeResult::Succeeded;
}
