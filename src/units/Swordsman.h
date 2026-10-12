#pragma once
#include "Infantry.h"

class Swordsman : public Infantry {
public:
    Swordsman() : Infantry(120, 15, 25) {}

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Swordsman>(*this);
    }
    std::string getType() const override { return "Swordsman"; }
    char getSymbol() const override { return 'S'; }
};