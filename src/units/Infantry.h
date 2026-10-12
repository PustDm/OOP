#pragma once
#include "Unit.h"

class Infantry : public Unit {
public:
    Infantry(int hp, int armor, int atk) : Unit(hp, armor, atk) {}
    std::string getCategory() const { return "Infantry"; }
};