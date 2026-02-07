#pragma once

#include <vector>
#include <functional>
#include <string>

/** * HP
*/
class AttributeComponent
{
public:
    /** *
    * @param InMaxHealth Staring max health
    */
    AttributeComponent(float InMaxHealth = 100.0f);

public:
    /** Health change: (NewHealth, Delta) */
    std::function<void(float, float)> OnHealthChanged;

    /** Death event */
    std::function<void()> OnDeath;

protected:
    /** * Max Health
    */
    float MaxHealth;

    /** * Current Health
    */
    float CurrentHealth;

private:
    /** * Flag of living
    */
    bool bIsAlive;

public:
    /** * HP Change
    * * @param Delta How much changed
    */
    void ApplyHealthChange(float Delta);

    /** * Returning current health
    * @return float
    */
    float GetHealth() const { return CurrentHealth; }

    /** * Returning max health
    * @return float
    */
    float GetMaxHealth() const { return MaxHealth; }

    /** * Check if guy is alive or not
    * @return bool
    */
    bool IsAlive() const { return bIsAlive; }

private:
    /** * Starting state
    */
    void Initialize();
};