#include "XMenBaseCharacter.h"

AXMenBaseCharacter::AXMenBaseCharacter()
{
    // Инициализация базовых значений характеристик персонажа
    Health = 100.0f;
    Armor = 50.0f;
    Damage = 25.0f;
    ActionPoints = 10.0f;
    bIsStunned = false;
    bIsBleeding = false;
    bIsTeleporting = false;
}

void AXMenBaseCharacter::UseAbility1()
{
    // Заглушка для способности 1
}

void AXMenBaseCharacter::UseAbility2()
{
    // Заглушка для способности 2
}

void AXMenBaseCharacter::UseBasicAttack()
{
    // Заглушка для базовой атаки
}

void AXMenBaseCharacter::ApplyStun()
{
    // Заглушка для применения оглушения
}

void AXMenBaseCharacter::ApplyBleeding()
{
    // Заглушка для применения кровотечения
}

void AXMenBaseCharacter::ApplyTeleport()
{
    // Заглушка для применения телепортации
}