#include "Base.h"
#include <iostream>
#include <algorithm>

Base::Base(int health, std::size_t maxUnits, int defenseLevel, int x, int y)
    : health_(health), maxHealth_(health), maxUnits_(maxUnits), 
      defenseLevel_(defenseLevel), resources_(0), x_(x), y_(y) {}

std::unique_ptr<Unit> Base::createUnit(const UnitFactory& factory, int x, int y) {
    if (units_.size() >= maxUnits_) {
        std::cout << "База: Лимит юнитов достигнут!\n";
        return nullptr;
    }

    auto unit = factory.createUnit();
    if (!unit) return nullptr;

    int id = nextUnitId_++;
    unit->setId(id);
    
    unit->subscribe(this);

    Unit* rawPtr = unit.get();
    units_.push_back(rawPtr);
    unitsById_[id] = rawPtr;

    UnitEvent createdEvent(EventType::Created, id);
    onUnitEvent(createdEvent);

    return unit;
}

void Base::onUnitEvent(const UnitEvent& event) {
    switch (event.type) {
        case EventType::Created:
            std::cout << "[База] Юнит #" << event.unit_id << " успешно создан.\n";
            break;

        case EventType::Damaged:
            std::cout << "[База] Юнит #" << event.unit_id 
                      << " получил урон: " << event.damage << "\n";
            break;

        case EventType::Destroyed:
            std::cout << "[База] Юнит #" << event.unit_id << " погиб! Убираем из учета.\n";
            unitsById_.erase(event.unit_id);
            units_.erase(
                std::remove(units_.begin(), units_.end(), nullptr), 
                units_.end()
            );
            break;
    }
}