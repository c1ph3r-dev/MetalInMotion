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
Get a ratio of a value between a minimum and maximum amount, optionally clamped.
*********************************************************************************/

static float GetRatio(const float Value, const float Minimum, const float Maximum, const bool bClamp = true)
{
	if (Value > Maximum && bClamp == true)
	{
		return 1.0f;
	}
	else if (Value > Minimum)
	{
		return (Value - Minimum) / (Maximum - Minimum);
	}
	else
	{
		return 0.0f;
	}
}

/**
Constructor for a goal for ball bearings.
*********************************************************************************/

ABallBearingGoal::ABallBearingGoal() :
	Magnetism(7500.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetActorHiddenInGame(false);
}

/**
Does this goal have a ball bearing resting in its center?
*********************************************************************************/

bool ABallBearingGoal::HasBallBearing() const
{
	const FVector OurLocation = GetActorLocation();

	for (const ABallBearing* BallBearing : BallBearings)
	{
		const FVector Difference = OurLocation - BallBearing->GetActorLocation();
		const float Distance = Difference.Size();

		if (Distance < 75.f)
			return true;
	}

	return false;
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

void ABallBearingGoal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector OurLocation = GetActorLocation();
	const float SphereRadius = Cast<USphereComponent>(GetCollisionComponent())->GetScaledSphereRadius();
	float LocalMagnetism = Magnetism;

	// If we're cheating then give our goals extra magnetism.

	static const IConsoleVariable* ExtraForce = IConsoleManager::Get().FindConsoleVariable(TEXT("OurGame.ExtraMagnetism"));

	if (ExtraForce && ExtraForce->GetInt() != 0)
		Magnetism *= 4.f;

	/// Now iterate around the proximate ball bearings and draw them towards our center
	/// using physics forces scaled by magnetism and distance from the center.

	for (const ABallBearing* BallBearing : BallBearings)
	{
		FVector Difference = OurLocation - BallBearing->GetActorLocation();
		const float Distance = Difference.Size();
		FVector Direction = Difference;

		Direction.Normalize();

		const float Ratio = GetRatio(Distance, 0.f, SphereRadius);
		const FVector Force = (1.f - Ratio) * Magnetism * Direction;

		BallBearing->BallMesh->AddForce(Force);
	}
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
