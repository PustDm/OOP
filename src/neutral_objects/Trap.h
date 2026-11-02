#pragma once
#include "NeutralObject.h"
#include "strategies/DamageStrategy.h"
#include "../units/Unit.h"

class Trap : public NeutralObject {
public:
    Trap() : NeutralObject(std::make_shared<DamageStrategy>(25)) {} // Фикс. урон 25
    char getSymbol() const override { return 'X'; }
};

inline void operator-(Unit& unit, const Trap& trap) {
    trap.interact(unit);
}