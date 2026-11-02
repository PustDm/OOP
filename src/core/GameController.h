#pragma once
#include "TerrainMap.h"
#include "../base/Base.h"
#include "../factories/InfantryFactory.h"
#include "../factories/ArcherFactory.h"

class GameController {
private:
    Base base_;
    TerrainMap map_;

public:
    GameController() 
        : base_(500, 10, 5, 0, 0),
          map_(15, 15, 10)
    {}

    Base& getBase() { return base_; }
    TerrainMap& getMap() { return map_; }

    bool createUnitOnMap(const UnitFactory& factory, int x, int y) {
        auto unit = base_.createUnit(factory, x, y);
        if (!unit) return false;

        try {
            map_.getField().addUnit(std::move(unit), x, y);
            return true;
        } catch (const std::exception& e) {
            std::cout << "Ошибка добавления на карту: " << e.what() << "\n";
            return false;
        }
    }
};