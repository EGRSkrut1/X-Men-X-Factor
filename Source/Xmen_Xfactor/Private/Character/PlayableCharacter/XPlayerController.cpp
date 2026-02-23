// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/PlayableCharacter/XPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create touch controls only for local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// Create mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// Add controls to player screen
			MobileControlsWidget->AddToPlayerScreen(0);
		}
	}
}

void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add IMC only for local player controllers
	if (IsLocalPlayerController())
	{
		// Add input mapping contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// Add these IMCs only if not using touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool AXPlayerController::ShouldUseTouchControls() const
{
	// Check if on mobile platform or force touch controls
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}