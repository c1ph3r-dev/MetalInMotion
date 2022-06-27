/**

Goals for ball bearings in Metal in Motion.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

These are generally used as the parent actor for goals within the game.

*********************************************************************************/

#include "BallBearingGoal.h"

#include "BallBearing.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"

/**
Constructor for a goal for ball bearings.
*********************************************************************************/

ABallBearingGoal::ABallBearingGoal()
{
	SetActorHiddenInGame(false);
}

/**
Hide the collision and sprite components in-game.
*********************************************************************************/

void ABallBearingGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCollisionComponent()->SetHiddenInGame(true);

#if WITH_EDITORONLY_DATA
	GetSpriteComponent()->SetHiddenInGame(true);
#endif
}

/**
Add a ball bearing to the list of proximate bearings we're maintaining.
*********************************************************************************/

void ABallBearingGoal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ABallBearing* BallBearing = Cast<ABallBearing>(OtherActor);

	if (BallBearing && BallBearing->Magnetized)
		BallBearings.AddUnique(BallBearing);
	
}

void ABallBearingGoal::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	ABallBearing* BallBearing = Cast<ABallBearing>(OtherActor);

	if(BallBearing && BallBearing->Magnetized)
		BallBearings.Remove(BallBearing);
}
