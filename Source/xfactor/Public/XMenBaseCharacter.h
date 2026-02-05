#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XMenBaseCharacter.generated.h"

UCLASS()
class XFACTOR_API AXMenBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AXMenBaseCharacter();

    // Заглушки для способностей
    UFUNCTION(BlueprintCallable)
    void UseAbility1();

    UFUNCTION(BlueprintCallable)
    void UseAbility2();

    UFUNCTION(BlueprintCallable)
    void UseBasicAttack();

    // Заглушки для состояний
    UFUNCTION(BlueprintCallable)
    void ApplyStun();

    UFUNCTION(BlueprintCallable)
    void ApplyBleeding();

    UFUNCTION(BlueprintCallable)
    void ApplyTeleport();

    // Заглушки для статов
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Armor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ActionPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsStunned;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsBleeding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTeleporting;
};