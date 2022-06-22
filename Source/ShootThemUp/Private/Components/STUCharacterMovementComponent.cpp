// Shoot Them Up Game. All Rights Reserved


#include "Components/STUCharacterMovementComponent.h"
#include "STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    ASTUBaseCharacter* const Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}

