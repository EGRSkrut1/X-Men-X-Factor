#include "XMenPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AXMenPlayerCharacter::AXMenPlayerCharacter()
{
    // Инициализация капсулы коллизии с заданными размерами
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Отключение вращения персонажа при повороте контроллера
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Настройка параметров движения персонажа
    GetCharacterMovement()->bOrientRotationToMovement = true;     // Персонаж поворачивается в направлении движения
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);  // Скорость поворота персонажа
    GetCharacterMovement()->JumpZVelocity = 500.f;                // Высота прыжка
    GetCharacterMovement()->AirControl = 0.35f;                   // Контроль в воздухе
    GetCharacterMovement()->MaxWalkSpeed = 500.f;                 // Максимальная скорость ходьбы

    // Создание и настройка стрелы камеры
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);                   // Прикрепление к корневому компоненту
    CameraBoom->TargetArmLength = 400.0f;                        // Длина стрелы (дистанция от персонажа)
    CameraBoom->bUsePawnControlRotation = true;                  // Стрела следует за вращением контроллера

    // Создание и настройка следящей камеры
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);  // Прикрепление к концу стрелы
    FollowCamera->bUsePawnControlRotation = false;               // Камера не следует за вращением контроллера напрямую
}

void AXMenPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Проверка наличия EnhancedInputComponent для современной системы ввода
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Привязка действия прыжка с проверкой наличия действия
        if (JumpAction)
        {
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        }

        // Привязка действия движения
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXMenPlayerCharacter::Move);
        }

        // Привязка действия поворота камеры мышью
        if (MouseLookAction)
        {
            EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AXMenPlayerCharacter::Look);
        }

        // Привязка действия поворота камеры геймпадом
        if (LookAction)
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AXMenPlayerCharacter::Look);
        }
    }
}

void AXMenPlayerCharacter::Move(const FInputActionValue& Value)
{
    // Получение вектора движения из значения ввода
    FVector2D MovementVector = Value.Get<FVector2D>();

    // Передача значений для обработки основного движения
    DoMove(MovementVector.X, MovementVector.Y);
}

void AXMenPlayerCharacter::Look(const FInputActionValue& Value)
{
    // Получение вектора поворота из значения ввода
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // Передача значений для обработки поворота камеры
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AXMenPlayerCharacter::DoMove(float Right, float Forward)
{
    // Проверка наличия контроллера для обработки ввода
    if (GetController() != nullptr)
    {
        // Получение текущего вращения контроллера
        const FRotator Rotation = GetController()->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);  // Извлечение только рыскания

        // Расчет векторов направления движения
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);  // Вперед
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);    // Вправо

        // Применение движения персонажа
        AddMovementInput(ForwardDirection, Forward);
        AddMovementInput(RightDirection, Right);
    }
}

void AXMenPlayerCharacter::DoLook(float Yaw, float Pitch)
{
    // Проверка наличия контроллера для обработки ввода
    if (GetController() != nullptr)
    {
        // Применение ввода поворота к контроллеру
        AddControllerYawInput(Yaw);    // Поворот по горизонтали
        AddControllerPitchInput(Pitch); // Поворот по вертикали
    }
}

void AXMenPlayerCharacter::DoJumpStart()
{
    // Вызов начала прыжка
    Jump();
}

void AXMenPlayerCharacter::DoJumpEnd()
{
    // Вызов окончания прыжка
    StopJumping();
}