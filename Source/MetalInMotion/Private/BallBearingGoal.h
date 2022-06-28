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

	// The power of the magnetism.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Goal)
	float Magnetism;

protected:
	// Hide the collision and sprite components in-game.
	virtual void PostInitializeComponents() override;

	// Add magnetism to the proximate ball bearings, drawing them towards our center.
	virtual void Tick(float DeltaSeconds) override;

	// Add a ball bearing to the list of proximate bearings we're maintaining.
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Remove a ball bearing from the list of proximate bearings we're maintaining.
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	// A list of proximate ball bearings.
	UPROPERTY(Transient)
	TArray<class ABallBearing*> BallBearings;
};
