#include "XAttributeComponent.h"

UXAttributeComponent::UXAttributeComponent()
{
    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;
    bIsAlive = true;

    UE_LOG(LogTemp, Log, TEXT("AttributeComponent Inititalized"));
}

void UXAttributeComponent::ApplyHealthChange(float Delta)
{
    // If characters is dead do not decrease HP
    if (!bIsAlive && Delta < 0.0f)
    {
        return;
    }

    float OldHealth = CurrentHealth;

    // Limit between 0 and max health.
    CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);

    float ActualDelta = CurrentHealth - OldHealth;

    // If changed
    if (ActualDelta != 0.0f)
    {
        // Change event
        OnHealthChanged.Broadcast(CurrentHealth, ActualDelta);
        

        // Check if dying
        if (CurrentHealth <= 0.0f && bIsAlive)
        {
            bIsAlive = false;
            OnDeath.Broadcast();
            
        }
    }
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