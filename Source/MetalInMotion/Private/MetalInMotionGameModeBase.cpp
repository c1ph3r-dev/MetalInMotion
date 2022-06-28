/**

The base game mode for Metal in Motion.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#include "MetalInMotionGameModeBase.h"

#include "BallBearingGoal.h"
#include "BallBearingHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

/**
Construct the game mode, assigning a debugging HUD class.
*********************************************************************************/

AMetalInMotionGameModeBase::AMetalInMotionGameModeBase() :
	FinishedTime(0.0f), bFinishedSoundPlayed(false)
{
	PrimaryActorTick.bCanEverTick = true;

	HUDClass = ABallBearingHUD::StaticClass();
}

void AMetalInMotionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if(BackgroundMusic)
		UGameplayStatics::PlaySound2D(AActor::GetWorld(), BackgroundMusic);
}

void AMetalInMotionGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Determine if all the goals have ball bearings at their center.

	int32 NumGoals = 0;
	bool bFinished = true;
	TArray<AActor*> Actors;

	// Note, GetAllActorsOfClass is generally not great for performance, but OK right here.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABallBearingGoal::StaticClass(), Actors);

	for (const AActor* Goal : Actors)
	{
		NumGoals++;
		if((Cast<ABallBearingGoal>(Goal))->HasBallBearing() == false)
		{
			bFinished = false;
			break;
		}
	}

	// If all goals are filled, then record how long that has been the case.
	if (NumGoals > 0 && bFinished)
		FinishedTime += DeltaSeconds;
	else
		FinishedTime = 0.0f;

	// If all goals have been filled for at least one second, then handle the finishing of the game.
	// The delay is to avoid ball bearings passing through the goals without stopping.
	if(FinishedTime > 1.f)
	{
		// Play the finished audio cue if not already done.
		if(!bFinishedSoundPlayed && FinishedSound)
		{
			bFinishedSoundPlayed = true;
			UGameplayStatics::PlaySound2D(GetWorld(), FinishedSound);
		}

		// If the game has been finished for at least 10 seconds then reset the game ready to go around again.
		if (FinishedTime > 10.0f)
		{
			Super::RestartGame();
		}
	}
}
