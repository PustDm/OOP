#pragma once
#include "../InteractionStrategy.h"
#include <iostream>

class ResourceStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) const override {
        std::cout << "[Стратегия] Юнит " << unit.getType() << " собрал золото для базы.\n";
    }
};