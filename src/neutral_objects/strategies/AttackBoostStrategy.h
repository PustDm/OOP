#include "../InteractionStrategy.h"

class AttackBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) const override {
        if (unit.getType() == "Swordsman" || unit.getType() == "Spearman") {
            unit.increaseAttack(10);
        } else {
            unit.increaseAttack(5);
        }
    }
};