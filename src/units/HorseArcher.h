#pragma once
#include "Cavalry.h"

class HorseArcher : public Cavalry {
public:
    HorseArcher() : Cavalry(100, 10, 30) {}

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<HorseArcher>(*this);
    }
    std::string getType() const override { return "HorseArcher"; }
    char getSymbol() const override { return 'h'; }
};