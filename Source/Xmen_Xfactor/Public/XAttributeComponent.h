#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XAttributeComponent.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionPointsChanged, int32, NewValue, int32, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class XMEN_XFACTOR_API UXAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UXAttributeComponent();

    // --- Delegates ---
    UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
    FOnHealthChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
    FOnActionPointsChanged OnActionPointsChanged;

    UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
    FOnDeath OnDeath;

protected:
    // --- Health ---
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes|Health")
    float MaxHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Health")
    float CurrentHealth;

    // --- Action Points ---
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes|ActionPoints")
    int32 MaxActionPoints;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|ActionPoints")
    int32 CurrentActionPoints;

    // --- Idetifiers ---

    /** * Slot of squad
     * 0 = Not in squad.
     * 1-4 = Number of slots in squad.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (ClampMin = "0", ClampMax = "4"))
    int32 SquadSlotIndex;

    /** Flag: NPC Ally */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    bool bIsAllyNPC;

    /** Flag: Enemy */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    bool bIsEnemy;

    /** Flag: Item */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    bool bIsInanimateObject;

private:
    bool bIsAlive;

public:
    // --- Health Methods ---
    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    bool ApplyHealthChange(float Delta);

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    bool ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    float GetHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
    bool IsAlive() const;

    // --- AP Methods ---
    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    bool ApplyActionPointsChange(int32 Delta);

    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    bool HasEnoughActionPoints(int32 Cost) const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    int32 GetActionPoints() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes|ActionPoints")
    int32 GetMaxActionPoints() const;

    // --- Identification methods ---

    /** Check if active in squad. */
    UFUNCTION(BlueprintCallable, Category = "Attributes|Identity")
    bool IsInPlayerSquad() const;

    /** Return slot number. */
    UFUNCTION(BlueprintCallable, Category = "Attributes|Identity")
    int32 GetSquadSlot() const;

    /** Set as enemy */
    UFUNCTION(BlueprintCallable, Category = "Attributes|Identity")
    void SetAsEnemy();

    /** Set as squad member. */
    UFUNCTION(BlueprintCallable, Category = "Attributes|Identity")
    void SetAsSquadMember(int32 NewSlotID);
};