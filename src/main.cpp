#include <iostream>
#include "core/GameController.h"
#include <cassert>
#include "field/GameField.h"
#include "factories/InfantryFactory.h"
#include "factories/ArcherFactory.h"
#include "factories/CavalryFactory.h"

void printMap(TerrainMap& map) {
    int w = map.getField().getWidth();
    int h = map.getField().getHeight();
    std::cout << "\033[37mX \033[0m"; 
    for (int x = 0; x < w; ++x) std::cout << "\033[37mX \033[0m"; 
    std::cout << "\033[37mX\033[0m\n";
    for (int y = 0; y < h; ++y) {
        std::cout << "\033[37mX \033[0m"; 
        
        for (int x = 0; x < w; ++x) {
            Unit* unit = map.getField().getUnit(x, y);
            if (unit) {
                std::cout << "\033[1;33m" << unit->getSymbol() << "\033[0m ";
                continue;
            }

            NeutralObject* obj = map.getNeutralObject(x, y);
            if (obj) {
                std::cout << "\033[1;31m" << obj->getSymbol() << "\033[0m ";
                continue;
            }

            Terrain* terrain = map.getTerrain(x, y);
            char sym = terrain->getSymbol();
            if (sym == '.')      std::cout << "\033[32m. \033[0m"; 
            else if (sym == '*') std::cout << "\033[1;32m* \033[0m"; 
            else if (sym == '~') std::cout << "\033[34m~ \033[0m"; 
            else if (sym == '^') std::cout << "\033[37m^ \033[0m"; 
            else                 std::cout << sym << " ";
        }
        std::cout << "\033[37mX\033[0m \n"; 
    }

    std::cout << "\033[37mX \033[0m"; 
    for (int x = 0; x < w; ++x) std::cout << "\033[37mX \033[0m"; 
    std::cout << "\033[37mX\033[0m\n\n";
}


int main() {
    std::cout << "Инициализация игры\n";
    GameController game;
    Base& base = game.getBase();
    TerrainMap& map = game.getMap();
    std::cout << "\nСценарий 1: Создание юнитов\n";
    InfantryFactory swordFactory(InfantryType::Swordsman);
    ArcherFactory archerFactory(ArcherType::Light);
    CavalryFactory cataFactory(CavalryType::Cataphract);

    game.createUnitOnMap(swordFactory, 0, 0);
    game.createUnitOnMap(archerFactory, 1, 0);
    game.createUnitOnMap(cataFactory, 2, 0);
    std::cout << "База создала юнитов. Всего в учете: " << base.getUnitCount() << "\n";
    std::cout << "\nСценарий 2: Перемещение и Прокси\n";
    map.moveUnit(0, 0, 0, 1);
    std::cout << "\nСценарий 3: Нейтральные объекты\n";
    map.addNeutralObject(1, 1, std::make_unique<TreasureChest>());
    map.addNeutralObject(2, 1, std::make_unique<Trap>());
    map.addNeutralObject(3, 1, std::make_unique<Altar>());
    map.addNeutralObject(4, 1, std::make_unique<EnergySource>());
    map.moveUnit(0, 1, 1, 1);
    map.moveUnit(1, 0, 2, 1);
    std::cout << "\nСценарий 4: Уничтожение юнита\n";
    Unit* archer = map.getField().getUnit(2, 1);
    if (archer) {
        std::cout << "Урон от ловушки...\n";
        archer->takeDamage(1000);
    }
    std::cout << "База после смерти юнита. Всего в учете: " << base.getUnitCount() << "\n";
    std::cout << "\nИгра завершена\n";
    std::cout << "\nКарта мира\n";
    printMap(map);
    return 0;
}