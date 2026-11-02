#pragma once
#include "../InteractionStrategy.h"
#include <iostream>

class DamageStrategy : public InteractionStrategy {
    int damage_;
public:
    explicit DamageStrategy(int dmg) : damage_(dmg) {}

    void apply(Unit& unit) const override {
        std::cout << "[Стратегия] Ловушка наносит " << damage_ << " урона.\n";
        unit.takeDamage(damage_);
    }
};