#include "Attack.h"
#include "Armor.h"

int Attack::calculateDamage(const Armor& targetArmor) const {
    return targetArmor.reduceDamage(value_);
}