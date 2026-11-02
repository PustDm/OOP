#pragma once
#include "NeutralObject.h"
#include "strategies/ResourceStrategy.h"
#include "../units/Unit.h"

class TreasureChest : public NeutralObject {
public:
    TreasureChest() : NeutralObject(std::make_shared<ResourceStrategy>()) {}
    char getSymbol() const override { return '$'; }
};

inline void operator+(Unit& unit, const TreasureChest& chest) {
    chest.interact(unit);
}