#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h" 
#include "XAttributeComponent.generated.h"

// Updated Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionPointsChanged, int32, NewValue, int32, Delta);
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

	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnStatusChanged OnStatusChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnDeath OnDeath;

protected:
	// --- CORE STATS ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	float CurrentHealth;

	// AP now int32
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 MaxActionPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 CurrentActionPoints;

	// --- IDENTITY ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (ClampMin = "0", ClampMax = "4"))
	int32 SquadSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool bIsAllyNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool bIsEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool bIsInanimateObject;

	// --- STATUS EFFECTS ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Tags")
	float BleedDamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Tags")
	float BleedTickInterval;

private:
	bool bIsAlive;
	FTimerHandle TimerHandle_Bleeding;

public:
	// --- HEALTH METHODS ---
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyDamage(float DamageAmount);

	// --- ACTION POINTS METHODS (Updated to int32) ---
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyActionPointsChange(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool HasEnoughActionPoints(int32 Cost) const;

	// --- STUN LOGIC ---
	/** Returns true if character has Status.Stunned tag */
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsStunned() const;

	// --- TAG MANAGEMENT ---
	UFUNCTION(BlueprintCallable, Category = "Attributes|Tags")
	void AddStatusTag(FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Attributes|Tags")
	void RemoveStatusTag(FGameplayTag TagToRemove);

	// --- GETTERS ---
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetActionPoints() const { return CurrentActionPoints; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const { return bIsAlive; }

protected:
	void HandleBleeding();
};