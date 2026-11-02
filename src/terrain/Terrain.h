#pragma once
#include <string>

class Terrain {
public:
    virtual ~Terrain() = default;
    virtual bool isPassable(const std::string& unitType) const = 0;
    virtual double getSpeedModifier(const std::string& unitType) const = 0;
    virtual int getDefenseBonus(const std::string& unitType) const = 0;
    virtual char getSymbol() const = 0;
};