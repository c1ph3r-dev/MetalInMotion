// Copyright Jonathan Justin Rampersad 2022

#pragma once

#include "CoreMinimal.h"
#include "EDifficulty.h"
#include "GameFramework/SaveGame.h"
#include "MetalInMotionSaveGame.generated.h"

UENUM(BlueprintType)
enum class ESpeedrunData: uint8
{
	ESD_L1 UMETA(DisplayName = "Level 1"),
	ESD_L2 UMETA(DisplayName = "Level 2"),
	ESD_L3 UMETA(DisplayName = "Level 3"),
	ESD_L4 UMETA(DisplayName = "Level 4"),
	ESD_L5 UMETA(DisplayName = "Level 5"),
	ESD_Total UMETA(DisplayName = "Total")
};

USTRUCT(BlueprintType)
struct FSpeedrunStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EDifficulty Difficulty = EDifficulty::ED_Normal;
	UPROPERTY(BlueprintReadWrite)
	ESpeedrunData Level;
	UPROPERTY(BlueprintReadWrite)
	int32 Minute = 999;
	UPROPERTY(BlueprintReadWrite)
	int32 Seconds = 999;
	UPROPERTY(BlueprintReadWrite)
	int32 Milliseconds =999;
};

/**
 * 
 */
UCLASS()
class METALINMOTION_API UMetalInMotionSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMetalInMotionSaveGame();

	UPROPERTY(EditAnywhere)
	TArray<FSpeedrunStruct> HighScores;
	
};
