#pragma once
#include "Player/STUPlayerState.h"

class STUUtils
{
public:
    template <typename T>
    static T* GetSTUPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        UActorComponent* Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    bool static AreEnemies(AController* Controller1, AController* Controller2)
    {
        if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

        const ASTUPlayerState* PlayerState1 = Controller1->GetPlayerState<ASTUPlayerState>();
        const ASTUPlayerState* PlayerState2 = Controller2->GetPlayerState<ASTUPlayerState>();

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }

    FText static FromStringToInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }
};
