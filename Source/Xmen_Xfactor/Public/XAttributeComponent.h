#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XAttributeComponent.generated.h"

// Delegate for Health
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
// Delegate for Action Points
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionPointsChanged, float, NewValue, float, Delta);
// Delegate for Death
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

/** * Attribute Component: Handles Health and Action Points
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class XMEN_XFACTOR_API UXAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    /** Constructor */
    UXAttributeComponent();

public:
    /** Triggered when Health changes */
    UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
    FOnHealthChanged OnHealthChanged;

    /** Triggered when Action Points change */
    UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
    FOnActionPointsChanged OnActionPointsChanged;

    /** Triggered when Health reaches 0 */
    UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
    FOnDeath OnDeath;

protected:
    /** Max Health */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes|Health")
    float MaxHealth;

    /** Current Health */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Health")
    float CurrentHealth;

    /** Max Action Points */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes|ActionPoints")
    float MaxActionPoints;

    /** Current Action Points */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|ActionPoints")
    float CurrentActionPoints;

private:
    /** Alive State Flag */
    bool bIsAlive;

public:
    /** * Modifies Health (Heal or Damage)
    * @param Delta Amount to change (negative for damage)
    * @return True if value actually changed
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    bool ApplyHealthChange(float Delta);

    /** * Helper function specifically for taking damage
    * @param DamageAmount Positive number representing damage
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    bool ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    float GetHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    bool IsAlive() const;

    /** * Modifies Action Points (Spend or Regain)
    * @param Delta Amount to change (negative to spend)
    * @return True if value actually changed
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    bool ApplyActionPointsChange(float Delta);

    /** * Check if character has enough AP for an action
    * @param Cost The cost of the action (positive number)
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    bool HasEnoughActionPoints(float Cost) const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    float GetActionPoints() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    float GetMaxActionPoints() const;
};