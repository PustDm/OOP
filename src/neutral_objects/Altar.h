#pragma once
#include "NeutralObject.h"
#include "strategies/AttackBoostStrategy.h"
#include "../units/Unit.h"

class Altar : public NeutralObject {
public:
    Altar() : NeutralObject(std::make_shared<AttackBoostStrategy>()) {}
    char getSymbol() const override { return 'A'; }
};

inline void operator*(Unit& unit, const Altar& altar) {
    altar.interact(unit);
}