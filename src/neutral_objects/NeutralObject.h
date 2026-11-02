#pragma once
#include "InteractionStrategy.h"
#include <memory>

class NeutralObject {
protected:
    std::shared_ptr<InteractionStrategy> strategy_;
public:
    NeutralObject(std::shared_ptr<InteractionStrategy> strategy) 
        : strategy_(strategy) {}
    
    virtual ~NeutralObject() = default;

    virtual void interact(Unit& unit) const {
        strategy_->apply(unit);
    }

    virtual char getSymbol() const = 0; 
};