/**

Main ball bearing implementation.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#include "BallBearing.h"

/**
Create a static mesh for this ball bearing on object construction.
*********************************************************************************/

ABallBearing::ABallBearing() :
	Magnetized(true),
	InContact(false),
	InitialLocation(FVector::ZeroVector)
{
 	// Set this pawn to call Tick() every frame.

	PrimaryActorTick.bCanEverTick = true;

	// Create the ball mesh, turn on its physics and set it as the root component.

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	
	BallMesh->SetSimulatePhysics(true);

	SetRootComponent(BallMesh);
}

void ABallBearing::ResetLocation() const
{
	BallMesh->SetWorldLocation(InitialLocation + FVector(0.f, 0.f, 150.f));
	BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

/**
Called when the game starts or when spawned.
*********************************************************************************/

void ABallBearing::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = BallMesh->GetComponentLocation();

	BallMesh->SetLinearDamping(.5f);
	BallMesh->SetAngularDamping(.5f);
}

/**
Control the movement of the ball bearing, called every frame.
*********************************************************************************/

void ABallBearing::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	InContact = false;
}

void ABallBearing::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	InContact = true;
}
