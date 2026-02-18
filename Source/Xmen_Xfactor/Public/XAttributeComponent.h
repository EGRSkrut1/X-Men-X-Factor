#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "XAttributeComponent.generated.h"

// Delegates.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionPointsChanged, float, NewValue, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChanged, FGameplayTag, Tag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class XMEN_XFACTOR_API UXAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UXAttributeComponent();

	// --- EVENTS ---
	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnActionPointsChanged OnActionPointsChanged;

	/** Triggered when a status tag is added or removed */
	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnStatusChanged OnStatusChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnDeath OnDeath;

protected:
	// --- EXISTING STATS ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|ActionPoints")
	float MaxActionPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|ActionPoints")
	float CurrentActionPoints;

	// --- GAMEPLAY TAGS ---

	/** Container holding all active status effects */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Tags")
	FGameplayTagContainer ActiveGameplayTags;

	/** How much damage Bleeding deals per tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Tags")
	float BleedDamageAmount;

	/** How often Bleeding ticks (in seconds) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Tags")
	float BleedTickInterval;

private:
	bool bIsAlive;
	FTimerHandle TimerHandle_Bleeding; // Internal timer for DoT

public:
	// --- TAG MANAGEMENT ---

	/** Adds a status effect */
	UFUNCTION(BlueprintCallable, Category = "Attributes|Tags")
	void AddStatusTag(FGameplayTag TagToAdd);

	/** Removes a status effect */
	UFUNCTION(BlueprintCallable, Category = "Attributes|Tags")
	void RemoveStatusTag(FGameplayTag TagToRemove);

	/** Checks if specific tag is active */
	UFUNCTION(BlueprintCallable, Category = "Attributes|Tags")
	bool HasStatusTag(FGameplayTag TagToCheck) const;

	// --- EXISTING METHODS ---

	UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
	bool ApplyHealthChange(float Delta);

	// Updated to check for STUN
	UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
	bool HasEnoughActionPoints(float Cost) const;

	// Rest of getters/setters/Identity
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const { return CurrentHealth; }

	// Identity logic needs to be here as well
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 SquadSlotIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool bIsInanimateObject;

protected:
	/** Internal function called by Timer to deal damage */
	void HandleBleeding();
};