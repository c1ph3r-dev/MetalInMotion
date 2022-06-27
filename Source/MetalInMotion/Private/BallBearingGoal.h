/**

Goals for ball bearings in Metal in Motion.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

These are generally used as the parent actor for goals within the game.

*********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "BallBearingGoal.generated.h"

/**
 * 
 */
UCLASS()
class ABallBearingGoal : public ATriggerSphere
{
	GENERATED_BODY()

public:
	// Constructor for a goal for ball bearings.
	ABallBearingGoal();

protected:
	// Hide the collision and sprite components in-game.
	virtual void PostInitializeComponents() override;

	// Add a ball bearing to the list of proximate bearings we're maintaining.
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Remove a ball bearing from the list of proximate bearings we're maintaining.
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	// A list of proximate ball bearings.
	UPROPERTY(Transient)
	TArray<class ABallBearing*> BallBearings;
};
