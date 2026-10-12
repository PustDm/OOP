#pragma once
#include "Unit.h"

class Cavalry : public Unit {
public:
    Cavalry(int hp, int armor, int atk) : Unit(hp, armor, atk) {}
    std::string getCategory() const { return "Cavalry"; }
};