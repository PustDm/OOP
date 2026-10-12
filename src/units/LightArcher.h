#pragma once
#include "Archer.h"

class LightArcher : public Archer {
public:
    LightArcher() : Archer(70, 5, 20) {}

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<LightArcher>(*this);
    }
    std::string getType() const override { return "LightArcher"; }
    char getSymbol() const override { return 'l'; }
};