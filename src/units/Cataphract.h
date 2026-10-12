#pragma once
#include "Cavalry.h"

class Cataphract : public Cavalry {
public:
    Cataphract() : Cavalry(150, 25, 35) {}

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Cataphract>(*this);
    }
    std::string getType() const override { return "Cataphract"; }
    char getSymbol() const override { return 'C'; }
};