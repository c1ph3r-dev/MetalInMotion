/**

Player ball bearing implementation.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#include "PlayerBallBearing.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


/**
Create a spring-arm and a camera for this ball bearing on object construction.
*********************************************************************************/

APlayerBallBearing::APlayerBallBearing() :
	ControllerForce(250.f), JumpForce(50.f), DashForce(150.f), MaximumSpeed(4.f),
	InputLongitude(0.f), InputLatitude(0.f), DashTimer(0.f)
{
	// Create a spring-arm attached to the ball mesh.

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.0f;

	SpringArm->SetupAttachment(GetRootComponent());

	// Create a camera and attach to the spring-arm.

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->bUsePawnControlRotation = false;

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Magnetized = false;
}


/**
Establish the default pawn input bindings for a player ball bearing.
*********************************************************************************/

static void InitializeDefaultPawnInputBindings()
{
	static bool bIndingsAdded = false;

	if (bIndingsAdded == false)
	{
		bIndingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Up, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Down, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Gamepad_LeftY, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Left, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Right, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Gamepad_LeftX, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Jump", EKeys::SpaceBar));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Dash", EKeys::Q));
	}
}


/**
Called to bind functionality to input.
*********************************************************************************/

void APlayerBallBearing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent != nullptr);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InitializeDefaultPawnInputBindings();

	PlayerInputComponent->BindAxis("BallBearing_MoveLongitudinally", this, &APlayerBallBearing::MoveLongitudinally);
	PlayerInputComponent->BindAxis("BallBearing_MoveLaterally", this, &APlayerBallBearing::MoveLaterally);

	PlayerInputComponent->BindAction("BallBearing_Jump", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Jump);
	PlayerInputComponent->BindAction("BallBearing_Dash", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Dash);
}


/**
Have the ball bearing perform a jump.
*********************************************************************************/

void APlayerBallBearing::Jump()
{
	// Only jump if we're in contact with something, normally the ground
	if(InContact)
		BallMesh->AddImpulse(FVector(0.f, 0.f, JumpForce * 1000.f));
}


/**
Have the ball bearing perform a dash.
*********************************************************************************/

void APlayerBallBearing::Dash()
{
	// Only dash if we're not dashing already.
	if (DashTimer == 0.f)
	{
		// Only dash if we have an existing velocity vector to dash towards.
		FVector Velocity = BallMesh->GetPhysicsLinearVelocity();
		if(Velocity.Size() > 1.f)
		{
			Velocity.Normalize();
			Velocity *= DashForce * 1000.f;

			// Add the impulse to the ball to perform the dash.
			BallMesh->AddImpulse(Velocity);

			// Set the length of time that we're to dash for.
			DashTimer = 1.5f;
		}
	}
}


/**
Control the movement of the ball bearing, called every frame.
*********************************************************************************/

void APlayerBallBearing::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Velocity = BallMesh->GetPhysicsLinearVelocity();
	float Z = Velocity.Z;
	Velocity.Z = 0.f;

	if(Velocity.Size() > MaximumSpeed * 100.f)
	{
		Velocity.Normalize();
		Velocity *= MaximumSpeed * 100.f;
		Velocity.Z = Z;

		float BreakingRatio = FMath::Pow(1.f - FMath::Min(DashTimer, 1.f), 2.f);

		FVector MergedVelocity = FMath::Lerp(BallMesh->GetPhysicsLinearVelocity(), Velocity, BreakingRatio);

		BallMesh->SetPhysicsLinearVelocity(MergedVelocity);
	}
	else
		BallMesh->AddForce(FVector(InputLongitude, InputLatitude, 0.0f) * ControllerForce * BallMesh->GetMass());

	if(DashTimer > 0.0f)
		DashTimer = FMath::Max(0.0f, DashTimer - DeltaSeconds);
}
