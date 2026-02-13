// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/XBaseCharacter.h"
#include "XTacticalCharacter.generated.h"

class UXAttributeComponent;

/**
 * 
 */
UCLASS()
class XMEN_XFACTOR_API AXTacticalCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:
	AXTacticalCharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UXAttributeComponent* AttributeComponent;
};
