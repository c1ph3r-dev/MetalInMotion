/**

Debugging HUD for Metal in Motion.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#include "DebugHUD.h"
#include "UObject/ConstructorHelpers.h"


/**
Construct the debugging HUD, mainly establishing a font to use for display.
*********************************************************************************/

ADebugHUD::ADebugHUD() :
	HorizontalOffset(150.f),
	X(50.f), Y(50.f), LineHeight(16.f)
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/Roboto"));

	MainFont = Font.Object;
}
