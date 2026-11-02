#pragma once
#include "../InteractionStrategy.h"
#include <iostream>

class HealthRestoreStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) const override {
        std::cout << "[Стратегия] Источник полностью восстанавливает здоровье.\n";
        unit.heal(9999);
    }
};