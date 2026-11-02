#pragma once
#include "Terrain.h"
#include <iostream>
#include <memory>

class TerrainProxy : public Terrain {
private:
    std::unique_ptr<Terrain> realTerrain_;

public:
    TerrainProxy(std::unique_ptr<Terrain> terrain) : realTerrain_(std::move(terrain)) {}

    bool isPassable(const std::string& unitType) const override {
        if (unitType == "FlyingUnit") return true;
        return realTerrain_->isPassable(unitType);
    }

    double getSpeedModifier(const std::string& unitType) const override {
        if (unitType == "FlyingUnit") return 1.0;
        return realTerrain_->getSpeedModifier(unitType);
    }

    int getDefenseBonus(const std::string& unitType) const override {
        return realTerrain_->getDefenseBonus(unitType);
    }

    char getSymbol() const override {
        return realTerrain_->getSymbol();
    }
};