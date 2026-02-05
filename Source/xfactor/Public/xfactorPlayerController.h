// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "xfactorPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 * Базовый класс PlayerController для игры от третьего лица.
 * Управляет контекстами ввода.
 */
UCLASS(abstract)
class AxfactorPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    /** Контексты сопоставления ввода */
    UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
    TArray<UInputMappingContext*> DefaultMappingContexts;

    /** Контексты сопоставления ввода, исключаемые для мобильных устройств */
    UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
    TArray<UInputMappingContext*> MobileExcludedMappingContexts;

    /** Виджет мобильного управления для создания */
    UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
    TSubclassOf<UUserWidget> MobileControlsWidgetClass;

    /** Указатель на виджет мобильного управления */
    UPROPERTY()
    TObjectPtr<UUserWidget> MobileControlsWidget;

    /** Если true, игрок будет использовать UMG сенсорное управление, даже если не на мобильной платформе */
    UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
    bool bForceTouchControls = false;

    /** Инициализация геймплея */
    virtual void BeginPlay() override;

    /** Настройка контекстов сопоставления ввода */
    virtual void SetupInputComponent() override;

    /** Возвращает true, если игрок должен использовать UMG сенсорное управление */
    bool ShouldUseTouchControls() const;
};