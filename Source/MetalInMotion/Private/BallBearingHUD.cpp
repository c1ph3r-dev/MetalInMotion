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

	const APlayerBallBearing* BallBearing = Cast<APlayerBallBearing>(GetOwningPawn());

	if (BallBearing != nullptr)
	{
	    const char* IC = "In contact"; size_t n = strlen(IC); const FString& Str_IC = FString(n, IC); const TCHAR* InContact = *Str_IC;
		const char* Spd = "Speed"; n = strlen(Spd); const FString& Str_Spd = FString(n, Spd); const TCHAR* Speed = *Str_Spd;
		const char* DT = "Dash timer"; n = strlen(DT); const FString& Str_DT = FString(n, DT); const TCHAR* DashTimer = *Str_DT;
		const char* ILA = "Input latitude"; n = strlen(ILA); const FString& Str_ILA = FString(n, ILA); const TCHAR* InLatitude = *Str_ILA;
		const char* ILO = "Input longitude"; n = strlen(ILO); const FString& Str_ILO = FString(n, ILO); const TCHAR* InLongitude = *Str_ILO;
		
		AddBool(InContact, BallBearing->InContact);
		AddFloat(Speed, BallBearing->GetVelocity().Size() / 100.0f);
		AddFloat(DashTimer, BallBearing->DashTimer);
		AddFloat(InLatitude, BallBearing->InputLatitude);
		AddFloat(InLongitude, BallBearing->InputLongitude);
	}
}
