#pragma once
#include "Terrain.h"
#include <string>

class Swamp : public Terrain {
public:
    bool isPassable(const std::string& unitType) const override {
        return true;
    }

    double getSpeedModifier(const std::string& unitType) const override {
        return 1.0;
    }

    int getDefenseBonus(const std::string& unitType) const override {
        return 0;
    }

    char getSymbol() const override {
        return '~';
    }
};