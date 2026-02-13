// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TacticalCharacter/XTacticalCharacter.h"
#include "XAttributeComponent.h"

AXTacticalCharacter::AXTacticalCharacter()
{
	AttributeComponent = CreateDefaultSubobject<UXAttributeComponent>("AttributeComponent");
}
