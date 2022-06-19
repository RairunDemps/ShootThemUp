// Shoot Them Up Game. All Rights Reserved


#include "STUGameInstance.h"
#include "Sound/SoundClass.h"
#include "Sound/STUSoundFuncLib.h"

void USTUGameInstance::ToggleSound()
{
    USTUSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
