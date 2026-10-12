#pragma once
#include "Unit.h"

class Archer : public Unit {
public:
    Archer(int hp, int armor, int atk) : Unit(hp, armor, atk) {}
    std::string getCategory() const { return "Archer"; }
};