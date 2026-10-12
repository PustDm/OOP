#include <iostream>
#include <cassert>
#include "field/GameField.h"
#include "factories/InfantryFactory.h"
#include "factories/ArcherFactory.h"
#include "factories/CavalryFactory.h"

static void printField(const GameField& field) {
    std::cout << "  ";
    for (int x = 0; x < field.getWidth(); ++x) std::cout << x % 10 << ' ';
    std::cout << '\n';
    for (int y = 0; y < field.getHeight(); ++y) {
        std::cout << y % 10 << ' ';
        for (int x = 0; x < field.getWidth(); ++x) {
            const Unit* u = field.getUnit(x, y);
            std::cout << (u ? u->getSymbol() : '.') << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::cout << "Создание поля и наполнение через фабрики\n";
    GameField field(8, 8, 16);
    InfantryFactory swordFactory(InfantryType::Swordsman);
    InfantryFactory spearFactory(InfantryType::Spearman);
    ArcherFactory   lightFactory(ArcherType::Light);
    ArcherFactory   heavyFactory(ArcherType::Heavy);
    CavalryFactory  cataFactory(CavalryType::Cataphract);
    CavalryFactory  horseFactory(CavalryType::HorseArcher);

    field.fillWithFactory(swordFactory, 2);
    field.fillWithFactory(spearFactory, 2);
    field.fillWithFactory(lightFactory, 2);
    field.fillWithFactory(heavyFactory, 1);
    field.fillWithFactory(cataFactory,  1);
    field.fillWithFactory(horseFactory, 1);

    printField(field);
    std::cout << "Всего юнитов: " << field.getSize() << "\n\n";

    std::cout << "Глубокое копирование\n";
    GameField copy = field;            // copy ctor
    Unit* original = field.getUnit(0, 0);
    Unit* cloned   = copy.getUnit(0, 0);
    assert(original && cloned && original != cloned);

    Unit* attacker = copy.getUnit(1, 0);
    if (attacker && cloned) {
        std::cout << "До атаки: clone HP = " << cloned->getHealth().getValue() << '\n';
        attacker->attackUnit(*cloned);
        std::cout << "После атаки: clone HP = " << cloned->getHealth().getValue()
                  << ", original HP = " << original->getHealth().getValue() << '\n';
    }
    std::cout << "Копия независима от оригинала.\n\n";

    std::cout << "Перемещение поля\n";
    GameField moved = std::move(field);
    std::cout << "После move: moved.getSize() = " << moved.getSize()
              << ", field.getSize() = " << field.getSize() << '\n';
    assert(field.getSize() == 0);
    std::cout << "Перемещение выполнено, исходное поле пусто.\n\n";

    std::cout << "Обход итератором\n";
    int idx = 0;
    for (Unit& u : moved) {
        std::cout << "#" << ++idx << " " << u.getType()
                  << " at (" << u.getX() << "," << u.getY() << ")"
                  << " HP=" << u.getHealth().getValue()
                  << " ARM=" << u.getArmor().getValue()
                  << " ATK=" << u.getAttack().getValue() << '\n';
    }
    std::cout << "Итерация завершена. Найдено юнитов: " << idx << '\n';

    return 0;
}