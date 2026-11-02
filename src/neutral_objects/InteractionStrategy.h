#pragma once
#include "../units/Unit.h"

class InteractionStrategy {
public:
    virtual ~InteractionStrategy() = default;
    virtual void apply(Unit& unit) const = 0;
};