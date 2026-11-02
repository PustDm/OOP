#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "../patterns/IObserver.h"
#include "../units/Unit.h"
#include "../factories/UnitFactory.h"

class Base : public IObserver {
private:
    int health_;
    int maxHealth_;
    std::size_t maxUnits_;
    int defenseLevel_;
    int resources_; 
    int x_, y_; 
    std::vector<Unit*> units_; 
    std::map<int, Unit*> unitsById_; 
    int nextUnitId_ = 1;
public:
    Base(int health, std::size_t maxUnits, int defenseLevel, int x, int y);
    ~Base() override = default;
    void onUnitEvent(const UnitEvent& event) override;
    std::unique_ptr<Unit> createUnit(const UnitFactory& factory, int x, int y);
    int getHealth() const { return health_; }
    std::size_t getUnitCount() const { return units_.size(); }
    const std::vector<Unit*>& getUnits() const { return units_; }
    int getResources() const { return resources_; }
};