/**

Player ball bearing implementation.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#pragma once

#include "BallBearing.h"
#include "PlayerBallBearing.generated.h"


/**
Player ball bearing class, processes input and possesses a camera.
*********************************************************************************/

UCLASS()
class METALINMOTION_API APlayerBallBearing : public ABallBearing
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties.
	APlayerBallBearing();

	// Spring arm for positioning the camera above the ball bearing.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing)
	class USpringArmComponent* SpringArm = nullptr;

	// Camera to view the ball bearing.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing)
	class UCameraComponent* Camera = nullptr;

	// How much force to use to push the ball bearing around.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float ControllerForce;

	// How much force to use to push the ball bearing into the air.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float JumpForce;
	
	// How much force to use to have the ball bearing dash.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float DashForce;

	// The maximum speed in meters per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
	float MaximumSpeed;

protected:

	// Control the movement of the ball bearing, called every frame.
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Move the ball bearing with the given force longitudinally on the X axis.
	FORCEINLINE void MoveLongitudinally(const float Value) { InputLongitude = Value; }

	// Move the ball bearing with the given force longitudinally on the Y axis.
	FORCEINLINE void MoveLaterally(const float Value) { InputLatitude = Value; }

	// Have the ball bearing perform a jump.
	void Jump();

	// Have the ball bearing perform a dash.
	void Dash();

	// The current longitude input received from the player.
	float InputLongitude;

	// The current latitude input received from the player.
	float InputLatitude;

	// Timer used to control the dashing of the ball bearing.
	float DashTimer;

	// Allow the ball bearing HUD unfettered access to this class.
	friend class ABallBearingHUD;
};
