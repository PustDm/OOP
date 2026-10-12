#pragma once
#include "UnitFactory.h"
#include "../units/Swordsman.h"
#include "../units/Spearman.h"

enum class InfantryType { Swordsman, Spearman };

class InfantryFactory : public UnitFactory {
private:
    InfantryType type_;
public:
    explicit InfantryFactory(InfantryType t) : type_(t) {}

    std::unique_ptr<Unit> createUnit() const override {
        switch (type_) {
            case InfantryType::Swordsman: return std::make_unique<Swordsman>();
            case InfantryType::Spearman:  return std::make_unique<Spearman>();
        }
        return nullptr;
    }
};