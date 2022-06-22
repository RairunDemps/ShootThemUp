// Shoot Them Up Game. All Rights Reserved

#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* const Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        USTUAIWeaponComponent* const WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUAIWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0.0f && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
