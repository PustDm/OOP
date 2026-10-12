#pragma once
#include "UnitFactory.h"
#include "../units/Cataphract.h"
#include "../units/HorseArcher.h"

enum class CavalryType { Cataphract, HorseArcher };

class CavalryFactory : public UnitFactory {
private:
    CavalryType type_;
public:
    explicit CavalryFactory(CavalryType t) : type_(t) {}

    std::unique_ptr<Unit> createUnit() const override {
        switch (type_) {
            case CavalryType::Cataphract:  return std::make_unique<Cataphract>();
            case CavalryType::HorseArcher: return std::make_unique<HorseArcher>();
        }
        return nullptr;
    }
};