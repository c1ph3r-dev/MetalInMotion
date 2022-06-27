/**

Ball bearing HUD for Metal in Motion.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#include "BallBearingHUD.h"
#include "PlayerBallBearing.h"


/**
Draw the HUD.
*********************************************************************************/

void ABallBearingHUD::DrawHUD()
{
	Super::DrawHUD();

	APlayerBallBearing* BallBearing = Cast<APlayerBallBearing>(GetOwningPawn());

	if (BallBearing != nullptr)
	{
		AddBool(L"In contact", BallBearing->InContact);
		AddFloat(L"Speed", BallBearing->GetVelocity().Size() / 100.0f);
		AddFloat(L"Dash timer", BallBearing->DashTimer);
		AddFloat(L"Input latitude", BallBearing->InputLatitude);
		AddFloat(L"Input longitude", BallBearing->InputLongitude);
	}
}
