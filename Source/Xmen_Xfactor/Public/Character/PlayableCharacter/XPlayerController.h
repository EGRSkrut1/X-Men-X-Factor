// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 * Base player controller for third-person gameplay
 * Manages input mapping contexts and touch controls
 */
UCLASS()
class XMEN_XFACTOR_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** Default input mapping contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping contexts excluded for mobile devices */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget class to spawn */
	UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, player will use UMG touch controls even if not on mobile platform */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Setup input mapping contexts */
	virtual void SetupInputComponent() override;

	/** Returns true if player should use UMG touch controls */
	bool ShouldUseTouchControls() const;
};