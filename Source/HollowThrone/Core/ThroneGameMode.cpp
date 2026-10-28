// Copyright - Adam Crofts


#include "ThroneGameMode.h"
#include "../Character/ThronePlayerController.h"


AThroneGameMode::AThroneGameMode()
{
	PlayerControllerClass = AThronePlayerController::StaticClass();
}
