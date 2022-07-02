// Copyright Jonathan Justin Rampersad 2022

#pragma once

#include "CoreMinimal.h"
#include "MetalInMotionSaveGame.h"
#include "Engine/GameInstance.h"
#include "MetalInMotionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class METALINMOTION_API UMetalInMotionGameInstance : public UGameInstance
{
	GENERATED_BODY()

	void Check(FSpeedrunStruct Data, int32 Level);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TArray<FSpeedrunStruct> HighScores;
	
	TArray<FSpeedrunStruct> TempScores;

public:
	UMetalInMotionGameInstance();
	
	UFUNCTION(BlueprintCallable)
	void NewScore(FSpeedrunStruct Data);

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	
};