#pragma once
#include "UnitFactory.h"
#include "../units/LightArcher.h"
#include "../units/HeavyArcher.h"

enum class ArcherType { Light, Heavy };

class ArcherFactory : public UnitFactory {
private:
    ArcherType type_;
public:
    explicit ArcherFactory(ArcherType t) : type_(t) {}

    std::unique_ptr<Unit> createUnit() const override {
        switch (type_) {
            case ArcherType::Light: return std::make_unique<LightArcher>();
            case ArcherType::Heavy: return std::make_unique<HeavyArcher>();
        }
        return nullptr;
    }
};