#include "XAttributeComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"

UXAttributeComponent::UXAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	MaxActionPoints = 10.0f;
	CurrentActionPoints = MaxActionPoints;
	bIsAlive = true;

	// Defaults for Bleeding
	BleedDamageAmount = 5.0f; // 5 damage per turn
	BleedTickInterval = 1.0f; // Every 1 turn
}

// ... ApplyHealthChange implementation ...

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
	if (!bIsAlive && Delta < 0.0f) return false;

	float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);
	float ActualDelta = CurrentHealth - OldHealth;

	if (ActualDelta != 0.0f)
	{
		OnHealthChanged.Broadcast(CurrentHealth, ActualDelta);
		if (CurrentHealth <= 0.0f && bIsAlive)
		{
			bIsAlive = false;
			OnDeath.Broadcast();

			// Clear all tags on death
			ActiveGameplayTags.Reset();
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Bleeding);
		}
		return true;
	}
	return false;
}

// --- TAG LOGIC ---

void UXAttributeComponent::AddStatusTag(FGameplayTag TagToAdd)
{
	ActiveGameplayTags.AddTag(TagToAdd);
	OnStatusChanged.Broadcast(TagToAdd);

	// Check if the tag is "Status.Bleeding"
	// Note: In real production, we usually use defined variables, but string check works for start
	if (TagToAdd.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Status.Bleeding"))))
	{
		// Start the timer if not already active
		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Bleeding))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Bleeding, this, &UXAttributeComponent::HandleBleeding, BleedTickInterval, true);
			UE_LOG(LogTemp, Log, TEXT("Bleeding Started!"));
		}
	}
}

void UXAttributeComponent::RemoveStatusTag(FGameplayTag TagToRemove)
{
	ActiveGameplayTags.RemoveTag(TagToRemove);
	OnStatusChanged.Broadcast(TagToRemove);

	// Check if we removed Bleeding
	if (TagToRemove.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Status.Bleeding"))))
	{
		// Stop the timer
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Bleeding);
		UE_LOG(LogTemp, Log, TEXT("Bleeding Stopped!"));
	}
}

bool UXAttributeComponent::HasStatusTag(FGameplayTag TagToCheck) const
{
	return ActiveGameplayTags.HasTag(TagToCheck);
}

void UXAttributeComponent::HandleBleeding()
{
	if (bIsAlive)
	{
		// Apply damage over time
		ApplyHealthChange(-BleedDamageAmount);
	}
	else
	{
		// Stop timer if dead
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Bleeding);
	}
}

// --- UPDATED ACTION POINT CHECK ---

bool UXAttributeComponent::HasEnoughActionPoints(float Cost) const
{
	// 1. Inanimate objects check
	if (bIsInanimateObject) return false;

	// 2. STUN CHECK
	// If character has "Status.Stunned", they cannot do anything
	if (ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Status.Stunned"))))
	{
		// Optional: Print debug message
		// UE_LOG(LogTemp, Warning, TEXT("Action Failed: Character is Stunned!"));
		return false;
	}

	// 3. Cost check
	return CurrentActionPoints >= Cost;
}