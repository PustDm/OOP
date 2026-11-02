#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include "../field/GameField.h"
#include "../terrain/TerrainProxy.h"
#include "../terrain/Plains.h"
#include "../terrain/Forest.h"
#include "../terrain/Swamp.h"
#include "../terrain/Mountains.h"
#include "../neutral_objects/NeutralObject.h"
#include "../neutral_objects/TreasureChest.h"
#include "../neutral_objects/Trap.h"
#include "../neutral_objects/Altar.h"
#include "../neutral_objects/EnergySource.h"

class TerrainMap {
private:
    int width_, height_;
    GameField field_;
    std::vector<std::unique_ptr<Terrain>> terrainGrid_;
    std::vector<std::unique_ptr<NeutralObject>> objectGrid_;

    std::size_t index(int x, int y) const { return y * width_ + x; }

public:
    TerrainMap(int w, int h, std::size_t maxUnits) 
        : width_(w), height_(h), field_(w, h, maxUnits), 
          terrainGrid_(w * h), objectGrid_(w * h) 
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100); 

        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                int chance = dist(gen);
                std::unique_ptr<Terrain> baseTerrain;

                if (chance <= 50)      baseTerrain = std::make_unique<Plains>();
                else if (chance <= 75) baseTerrain = std::make_unique<Forest>();
                else if (chance <= 90) baseTerrain = std::make_unique<Swamp>();
                else                   baseTerrain = std::make_unique<Mountains>();

                terrainGrid_[index(x, y)] = std::make_unique<TerrainProxy>(std::move(baseTerrain));
            }
        }
    }

    void addNeutralObject(int x, int y, std::unique_ptr<NeutralObject> obj) {
        objectGrid_[index(x, y)] = std::move(obj);
    }

    NeutralObject* getNeutralObject(int x, int y) {
        return objectGrid_[index(x, y)].get();
    }

    Terrain* getTerrain(int x, int y) { return terrainGrid_[index(x, y)].get(); }
    GameField& getField() { return field_; }

    bool moveUnit(int fromX, int fromY, int toX, int toY) {
        Unit* unit = field_.getUnit(fromX, fromY);
        if (!unit) return false;

        Terrain* terrain = getTerrain(toX, toY);
        std::string type = unit->getType();

        if (!terrain->isPassable(type)) {
            std::cout << "Юнит " << type << " не может пройти на эту клетку (Ландшафт).\n";
            return false;
        }

        try {
            field_.moveUnit(fromX, fromY, toX, toY);
            std::cout << "Юнит " << type << " переместился на (" << toX << "," << toY << ").\n";

            NeutralObject* obj = getNeutralObject(toX, toY);
            if (obj) {
                std::cout << "На клетке обнаружен объект [" << obj->getSymbol() << "]. Взаимодействие...\n";
                
                if (dynamic_cast<TreasureChest*>(obj)) {
                    *unit + *dynamic_cast<TreasureChest*>(obj);
                } else if (dynamic_cast<Trap*>(obj)) {
                    *unit - *dynamic_cast<Trap*>(obj);
                } else if (dynamic_cast<Altar*>(obj)) {
                    *unit * *dynamic_cast<Altar*>(obj);
                } else if (dynamic_cast<EnergySource*>(obj)) {
                    *unit / *dynamic_cast<EnergySource*>(obj);
                }
            }
            return true;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
            return false;
        }
    }
};