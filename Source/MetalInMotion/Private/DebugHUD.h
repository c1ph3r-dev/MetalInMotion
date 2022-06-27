/**

Debugging HUD for Metal in Motion.

Original author: Rob Baker.
Current maintainer: Jonathan Rampersad.

*********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "CanvasItem.h"
#include "DebugHUD.generated.h"

/**
Debugging HUD for Metal in Motion, a base class for deriving implementations from.
*********************************************************************************/

UCLASS()
class METALINMOTION_API ADebugHUD : public AHUD
{
	GENERATED_BODY()

protected:

	// Construct the debugging HUD, mainly establishing a font to use for display.
	ADebugHUD();

	// Add a FText to the HUD for rendering.
	FORCEINLINE void AddText(const TCHAR* Title, const FText& Value) { RenderStatistic(Title, Value); }

	// Add a float to the HUD for rendering.
	FORCEINLINE void AddFloat(const TCHAR* Title, float Value) { RenderStatistic(Title, FText::AsNumber(Value)); }

	// Add an int32 to the HUD for rendering.
	FORCEINLINE void AddInt(const TCHAR* Title, int32 Value) { RenderStatistic(Title, FText::AsNumber(Value)); }

	// Add a bool to the HUD for rendering.
	FORCEINLINE void AddBool(const TCHAR* Title, bool bValue) { RenderStatistic(Title, BoolToText(bValue), (bValue == false) ? FLinearColor::Red : FLinearColor::Green); }

	// Draw the HUD.
	FORCEINLINE virtual void DrawHUD() override { X = Y = 50.0f; }

	// The horizontal offset to render the statistic values at.
	float HorizontalOffset;

private:

	// Convert a TCHAR pointer to FText.
	FORCEINLINE FText CStringToText(const TCHAR* Text) { return FText::FromString(Text); }

	// Convert a bool to FText.
	FORCEINLINE FText BoolToText(bool bValue) { return CStringToText((bValue == true) ? TEXT("true") : TEXT("false")); }

	// Render a statistic onto the HUD canvas.
	void RenderStatistic(const TCHAR* Title, const FText& Value, const FLinearColor& ValueColor = FLinearColor::Green)
	{
		FCanvasTextItem item0(FVector2D(X, Y), CStringToText(Title), MainFont, FLinearColor::White);
		item0.EnableShadow(FLinearColor(0.0f, 0.0f, 0.0f));
		Canvas->DrawItem(item0);
		FCanvasTextItem item1(FVector2D(X + HorizontalOffset, Y), Value, MainFont, ValueColor);
		item1.EnableShadow(FLinearColor(0.0f, 0.0f, 0.0f));
		Canvas->DrawItem(item1);
		Y += LineHeight;
	}

	// Font used to render the debug information.
	UPROPERTY(Transient)
	UFont* MainFont = nullptr;

	// The current X coordinate.
	float X;

	// The current Y coordinate.
	float Y;

	// The line height to separate each HUD entry.
	float LineHeight;
};
