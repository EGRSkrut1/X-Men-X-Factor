// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "xfactorGameMode.generated.h"

/**
 * Простой GameMode для игры от третьего лица
 */
UCLASS(abstract)
class AxfactorGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    /** Конструктор */
    AxfactorGameMode();
};