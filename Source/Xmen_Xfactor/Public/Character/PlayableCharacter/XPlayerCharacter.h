// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/XBaseCharacter.h"
#include "XPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

/**
 * Playable character with third-person camera controls
 */
UCLASS()
class XMEN_XFACTOR_API AXPlayerCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:
	AXPlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Handle movement input */
	void Move(const FInputActionValue& Value);

	/** Handle camera look input */
	void Look(const FInputActionValue& Value);

	/** Core movement logic */
	void DoMove(float Right, float Forward);

	/** Core camera look logic */
	void DoLook(float Yaw, float Pitch);

	/** Start jump */
	void DoJumpStart();

	/** End jump */
	void DoJumpEnd();

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	/** Follow camera for third-person view */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	/** Input action for jumping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	/** Input action for movement (forward/back, left/right) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	/** Input action for camera look (gamepad) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	/** Input action for camera look (mouse) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MouseLookAction;
};