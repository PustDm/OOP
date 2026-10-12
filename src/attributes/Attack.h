#pragma once

class Attack {
private:
    int value_;
public:
    explicit Attack(int v = 0) : value_(v > 0 ? v : 0) {}
    int calculateDamage(const class Armor& targetArmor) const;
    int getValue() const { return value_; }
};