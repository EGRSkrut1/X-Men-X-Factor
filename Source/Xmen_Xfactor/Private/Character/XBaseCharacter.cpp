// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XBaseCharacter.h"

// Sets default values
AXBaseCharacter::AXBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

