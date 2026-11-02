#pragma once
#include "NeutralObject.h"
#include "strategies/HealthRestoreStrategy.h"
#include "../units/Unit.h"

class EnergySource : public NeutralObject {
public:
    EnergySource() : NeutralObject(std::make_shared<HealthRestoreStrategy>()) {}
    char getSymbol() const override { return '+'; }
};

inline void operator/(Unit& unit, const EnergySource& source) {
    source.interact(unit);
}