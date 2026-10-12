#pragma once
#include "Archer.h"

class HeavyArcher : public Archer {
public:
    HeavyArcher() : Archer(90, 12, 28) {}

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<HeavyArcher>(*this);
    }
    std::string getType() const override { return "HeavyArcher"; }
    char getSymbol() const override { return 'H'; }
};