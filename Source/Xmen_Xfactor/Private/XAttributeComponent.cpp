#include "XAttributeComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"

	UXAttributeComponent::UXAttributeComponent()
	{
		PrimaryComponentTick.bCanEverTick = false;

		MaxHealth = 100.0f;
		CurrentHealth = MaxHealth;

		
		MaxActionPoints = 10;
		CurrentActionPoints = MaxActionPoints;

		bIsAlive = true;
		SquadSlotIndex = 0;
		bIsAllyNPC = false;
		bIsEnemy = false;
		bIsInanimateObject = false;

		BleedDamageAmount = 5.0f;
		BleedTickInterval = 1.0f;
	}

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
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Bleeding);
			}
			return true;
		}
		return false;
	}

	bool UXAttributeComponent::ApplyDamage(float DamageAmount)
	{
		return ApplyHealthChange(-FMath::Abs(DamageAmount));
	}

	// --- AP and stun ---

	bool UXAttributeComponent::IsStunned() const
	{
		// Tag check for stun
		return ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Status.Stunned")));
	}

	bool UXAttributeComponent::ApplyActionPointsChange(int32 Delta)
	{
		if (bIsInanimateObject) return false;

		// Stun blocking actions
		if (Delta < 0 && IsStunned())
		{
			UE_LOG(LogTemp, Warning, TEXT("Action Failed: %s is STUNNED"), *GetOwner()->GetName());
			return false;
		}

		int32 OldAP = CurrentActionPoints;
		CurrentActionPoints = FMath::Clamp(CurrentActionPoints + Delta, 0, MaxActionPoints);
		int32 ActualDelta = CurrentActionPoints - OldAP;

		if (ActualDelta != 0)
		{
			OnActionPointsChanged.Broadcast(CurrentActionPoints, ActualDelta);
			return true;
		}
		return false;
	}

	bool UXAttributeComponent::HasEnoughActionPoints(int32 Cost) const
	{
		if (bIsInanimateObject) return false;

		// Stunned no actions
		if (IsStunned()) return false;

		return CurrentActionPoints >= Cost;
	}

	// --- TAGS & BLEEDING ---

	void UXAttributeComponent::AddStatusTag(FGameplayTag TagToAdd)
	{
		ActiveGameplayTags.AddTag(TagToAdd);
		OnStatusChanged.Broadcast(TagToAdd);

		if (TagToAdd.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Status.Bleeding"))))
		{
			if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Bleeding))
			{
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_Bleeding, this, &UXAttributeComponent::HandleBleeding, BleedTickInterval, true);
			}
		}
	}

	void UXAttributeComponent::RemoveStatusTag(FGameplayTag TagToRemove)
	{
		ActiveGameplayTags.RemoveTag(TagToRemove);
		OnStatusChanged.Broadcast(TagToRemove);

		if (TagToRemove.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Status.Bleeding"))))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Bleeding);
		}
	}

	void UXAttributeComponent::HandleBleeding()
	{
		if (bIsAlive) ApplyHealthChange(-BleedDamageAmount);
		else GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Bleeding);
	}