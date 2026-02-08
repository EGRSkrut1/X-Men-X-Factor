#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

/** 
* HP
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class XMEN_XFACTOR_API UXAttributeComponent : public UActorComponent
{

    GENERATED_BODY()

public:
    /** *
    * @param InMaxHealth Staring max health
    */
    UXAttributeComponent();

public:
    /** Health change: (NewHealth, Delta) */
    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnHealthChanged OnHealthChanged;

    /** Death event */
    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnDeath OnDeath;

protected:
    /** 
    * Max Health
    */
    UPROPERTY(EditDefaultsOnly, Category = "Attributes")
    float MaxHealth;

    /** 
    * Current Health
    */
    UPROPERTY(EditDefaultsOnly, Category = "Attributes")
    float CurrentHealth;

private:
    /** 
    * Flag of living
    */
    bool bIsAlive;

public:
    /** 
    * HP Change
    * 
    * @param Delta How much changed
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void ApplyHealthChange(float Delta);

    /** 
    * Returning current health
    * @return float
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetHealth() const;

    /**
    * Returning max health
    * @return float
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMaxHealth() const;

    /** 
    * Check if guy is alive or not
    * @return alive status
    */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool IsAlive() const;
};