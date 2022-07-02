#pragma once
/**

Enum for difficulty

Original author: Jonathan Rampersad.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EDifficulty.generated.h"

UENUM(BlueprintType)
enum class EDifficulty : uint8 {
	ED_Normal UMETA(DisplayName = "Normal"),
	ED_Hard UMETA(DisplayName = "Hard")
};