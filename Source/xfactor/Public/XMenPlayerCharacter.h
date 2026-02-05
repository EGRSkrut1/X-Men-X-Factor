#pragma once
#include "CoreMinimal.h"
#include "XMenBaseCharacter.h"
#include "XMenPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class XFACTOR_API AXMenPlayerCharacter : public AXMenBaseCharacter
{
    GENERATED_BODY()

public:
    /** Конструктор игрового персонажа */
    AXMenPlayerCharacter();

protected:
    /** Настройка привязок ввода игрока */
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    /** Обработка ввода движения */
    void Move(const FInputActionValue& Value);

    /** Обработка ввода поворота камеры */
    void Look(const FInputActionValue& Value);

    /** Основная логика движения персонажа */
    void DoMove(float Right, float Forward);

    /** Основная логика поворота камеры */
    void DoLook(float Yaw, float Pitch);

    /** Начало прыжка */
    void DoJumpStart();

    /** Окончание прыжка */
    void DoJumpEnd();

public:
    /** Стрела камеры для позиционирования камеры позади персонажа */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    /** Следящая камера от третьего лица */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    /** Действие ввода для прыжка */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpAction;

    /** Действие ввода для движения (вперед/назад, влево/вправо) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;

    /** Действие ввода для поворота камеры (геймпад) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* LookAction;

    /** Действие ввода для поворота камеры (мышь) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MouseLookAction;
};