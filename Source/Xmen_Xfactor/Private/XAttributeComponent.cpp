#include "XAttributeComponent.h"

UXAttributeComponent::UXAttributeComponent()
{
    // Initialize Health
    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;
    bIsAlive = true;

    // Initialize Action Points
    MaxActionPoints = 10.0f; // Default value, can be changed in Blueprint
    CurrentActionPoints = MaxActionPoints;

    UE_LOG(LogTemp, Log, TEXT("AttributeComponent Initialized"));
}

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
    // 1. If dead and taking damage, ignore.
    if (!bIsAlive && Delta < 0.0f)
    {
        return false;
    }

    float OldHealth = CurrentHealth;

    // 2. Clamp between 0 and Max
    CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);

    float ActualDelta = CurrentHealth - OldHealth;

    // 3. Only broadcast if value actually changed
    if (ActualDelta != 0.0f)
    {
        OnHealthChanged.Broadcast(CurrentHealth, ActualDelta);

        // Check for Death
        if (CurrentHealth <= 0.0f && bIsAlive)
        {
            bIsAlive = false;
            OnDeath.Broadcast();

            UE_LOG(LogTemp, Warning, TEXT("AttributeComponent: Death message placeholder, whatever Artem waill want."));
        }
        return true;
    }

    return false;
}

bool UXAttributeComponent::ApplyDamage(float DamageAmount)
{
    // Simply calls Change with a negative value
    // Abs ensures we always pass a negative number even if user passes -50
    return ApplyHealthChange(-FMath::Abs(DamageAmount));
}

bool UXAttributeComponent::ApplyActionPointsChange(float Delta)
{
    float OldActionPoints = CurrentActionPoints;

    // Limit between 0 and Max Action Points
    CurrentActionPoints = FMath::Clamp(CurrentActionPoints + Delta, 0.0f, MaxActionPoints);

    float ActualDelta = CurrentActionPoints - OldActionPoints;

    // If the value actually changed
    if (ActualDelta != 0.0f)
    {
        OnActionPointsChanged.Broadcast(CurrentActionPoints, ActualDelta);
        return true;
    }

    return false;
}

bool UXAttributeComponent::HasEnoughActionPoints(float Cost) const
{
    return CurrentActionPoints >= Cost;
}

float UXAttributeComponent::GetMaxHealth() const
{
    return MaxHealth;
}

float UXAttributeComponent::GetHealth() const
{
    return CurrentHealth;
}

bool UXAttributeComponent::IsAlive() const
{
    return bIsAlive;
}

float UXAttributeComponent::GetActionPoints() const
{
    return CurrentActionPoints;
}

float UXAttributeComponent::GetMaxActionPoints() const
{
    return MaxActionPoints;
}