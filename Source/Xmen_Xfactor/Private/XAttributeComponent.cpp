#include "XAttributeComponent.h"
#include <algorithm> // For std::clamp
#include <iostream>  // Like UE_LOG

AttributeComponent::AttributeComponent(float InMaxHealth)
{
    MaxHealth = InMaxHealth;
    CurrentHealth = MaxHealth;
    bIsAlive = true;

    Initialize();
}

void AttributeComponent::Initialize()
{
    // Starting HP check
    bIsAlive = (CurrentHealth > 0.0f);

    // Console status
    std::cout << "[AttributeSystem] Component Initialized with " << MaxHealth << " HP." << std::endl;
}

void AttributeComponent::ApplyHealthChange(float Delta)
{
    // If characters is dead do not decrease HP
    if (!bIsAlive && Delta < 0.0f)
    {
        return;
    }

    float OldHealth = CurrentHealth;

    // Limit between 0 and max health.
    CurrentHealth = std::clamp(CurrentHealth + Delta, 0.0f, MaxHealth);

    float ActualDelta = CurrentHealth - OldHealth;

    // If changed
    if (ActualDelta != 0.0f)
    {
        // Change event
        if (OnHealthChanged)
        {
            OnHealthChanged(CurrentHealth, ActualDelta);
        }

        // Check if dying
        if (CurrentHealth <= 0.0f && bIsAlive)
        {
            bIsAlive = false;
            if (OnDeath)
            {
                OnDeath();
            }
        }
        // Ressurection
        else if (CurrentHealth > 0.0f && !bIsAlive)
        {
            bIsAlive = true;
        }
    }
}