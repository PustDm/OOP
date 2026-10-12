#pragma once
#include "Infantry.h"

class Spearman : public Infantry {
public:
    Spearman() : Infantry(100, 10, 30) {}

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Spearman>(*this);
    }
    std::string getType() const override { return "Spearman"; }
    char getSymbol() const override { return 'P'; }
};