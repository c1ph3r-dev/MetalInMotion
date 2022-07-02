// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MetalInMotionSaveGame.h"
#include "GameFramework/GameMode.h"
#include "MetalInMotionGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class METALINMOTION_API AMetalInMotionGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	// Construct the game mode, assigning a debugging HUD class.
	AMetalInMotionGameModeBase();

	// The sound cue to play for the background music.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
	class USoundCue* BackgroundMusic;

	// The sound cue to play when the game has been finished by the player.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
	USoundCue* FinishedSound;

	UFUNCTION(BlueprintCallable)
	void SetLevel(const ESpeedrunData LevelName) { Level = LevelName; }

protected:
	// Play the background music at the beginning of the game.
	virtual void BeginPlay() override;

	// Manage the game mode, mostly detecting and implementing the end-game state.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent)
	void EndTimer();

private:
	// The amount of time that the game has been finished.
	float FinishedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	EDifficulty Difficulty;

	// Has the finished sound been played?
	bool bFinishedSoundPlayed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	ESpeedrunData Level;

	void NextLevel() const;
};
