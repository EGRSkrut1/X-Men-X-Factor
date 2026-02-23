#include "XAttributeComponent.h"
#include "Math/UnrealMathUtility.h" // Required for FMath::Clamp and FMath::Abs

UXAttributeComponent::UXAttributeComponent()
{
    // Optimization: We don't need this component to run every frame
    PrimaryComponentTick.bCanEverTick = false;

    // --- 1. Health Initialization ---
    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;
    bIsAlive = true;

    // --- 2. Action Points Initialization ---
    MaxActionPoints = 10;
    CurrentActionPoints = MaxActionPoints;

    // --- 3. Identity Initialization (Default: Neutral NPC) ---
    SquadSlotIndex = 0;      // 0 = Not in player squad
    bIsAllyNPC = false;      // Not a generic ally
    bIsEnemy = false;        // Not an enemy
    bIsInanimateObject = false; // Is a living character

    UE_LOG(LogTemp, Log, TEXT("XAttributeComponent: Initialized"));
}

// ==============================================================================
// HEALTH SYSTEM
// ==============================================================================

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
    // Logic: Dead characters cannot take more damage (unless we add "Gibs" later)
    if (!bIsAlive && Delta < 0.0f)
    {
        return false;
    }

    // Logic: Inanimate objects (like whatever Artem thinks is the item) might take damage, but maybe not Heal?
    // For now, we allow both, but you can add specific logic here:
    // if (bIsInanimateObject && Delta > 0.0f) return false; // Objects can't heal

    float OldHealth = CurrentHealth;

    // Apply Math: Clamp ensures Health never goes below 0 or above Max
    CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);

    float ActualDelta = CurrentHealth - OldHealth;

    // Only broadcast if value actually changed
    if (ActualDelta != 0.0f)
    {
        OnHealthChanged.Broadcast(CurrentHealth, ActualDelta);

        // Death Check
        if (CurrentHealth <= 0.0f && bIsAlive)
        {
            bIsAlive = false;

            // Broadcast death so Character can play Ragdoll/Animation
            OnDeath.Broadcast();

            UE_LOG(LogTemp, Warning, TEXT("XAttributeComponent: Owner [%s] has Died/Destroyed."), *GetOwner()->GetName());
        }
        return true;
    }

    return false;
}

bool UXAttributeComponent::ApplyDamage(float DamageAmount)
{
    // Helper: Converts positive damage number (50) to negative delta (-50)
    // FMath::Abs ensures safety in case someone accidentally passes -50
    return ApplyHealthChange(-FMath::Abs(DamageAmount));
}

float UXAttributeComponent::GetHealth() const
{
    return CurrentHealth;
}

float UXAttributeComponent::GetMaxHealth() const
{
    return MaxHealth;
}

bool UXAttributeComponent::IsAlive() const
{
    return bIsAlive;
}

// ==============================================================================
// ACTION POINTS (AP) SYSTEM
// ==============================================================================

bool UXAttributeComponent::ApplyActionPointsChange(int32 Delta)
{
    // Logic: Inanimate objects usually don't have AP.
    if (bIsInanimateObject)
    {
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
    // Inanimate objects have no AP
    if (bIsInanimateObject)
    {
        return false;
    }
    return CurrentActionPoints >= Cost;
}

int32 UXAttributeComponent::GetActionPoints() const
{
    return CurrentActionPoints;
}

int32 UXAttributeComponent::GetMaxActionPoints() const
{
    return MaxActionPoints;
}

// ==============================================================================
// IDENTITY / SQUAD SYSTEM
// ==============================================================================

bool UXAttributeComponent::IsInPlayerSquad() const
{
    // If Slot is 1, 2, 3, or 4, they are in the active squad
    return SquadSlotIndex >= 1 && SquadSlotIndex <= 4;
}

int32 UXAttributeComponent::GetSquadSlot() const
{
    return SquadSlotIndex;
}

void UXAttributeComponent::SetAsEnemy()
{
    bIsEnemy = true;

    // Safety: An enemy cannot be in the player's squad or an ally
    bIsAllyNPC = false;
    SquadSlotIndex = 0;
}

void UXAttributeComponent::SetAsSquadMember(int32 NewSlotID)
{
    // Clamp to valid squad slots (1-4)
    SquadSlotIndex = FMath::Clamp(NewSlotID, 1, 4);

    // Safety: Squad members are not enemies
    bIsEnemy = false;
    bIsAllyNPC = false; // They are controlled characters, not NPCs
}