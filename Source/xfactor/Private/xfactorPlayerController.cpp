// Copyright Epic Games, Inc. All Rights Reserved.

#include "xfactorPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "xfactor.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AxfactorPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Создаем сенсорные элементы управления только для локальных контроллеров игрока
    if (ShouldUseTouchControls() && IsLocalPlayerController())
    {
        // Создание виджета мобильного управления
        MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

        if (MobileControlsWidget)
        {
            // Добавление элементов управления на экран игрока
            MobileControlsWidget->AddToPlayerScreen(0);
        }
        else
        {
            UE_LOG(Logxfactor, Error, TEXT("Could not spawn mobile controls widget."));
        }
    }
}

void AxfactorPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Добавляем IMC только для локальных контроллеров игрока
    if (IsLocalPlayerController())
    {
        // Добавление контекстов сопоставления ввода
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
            for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
            {
                Subsystem->AddMappingContext(CurrentContext, 0);
            }

            // Добавляем эти IMC только если не используем сенсорный ввод
            if (!ShouldUseTouchControls())
            {
                for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
                {
                    Subsystem->AddMappingContext(CurrentContext, 0);
                }
            }
        }
    }
}

bool AxfactorPlayerController::ShouldUseTouchControls() const
{
    // Находимся ли мы на мобильной платформе? Следует ли принудительно использовать сенсорный ввод?
    return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}