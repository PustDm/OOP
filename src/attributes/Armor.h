#pragma once

class Armor {
private:
    int value_;
public:
    explicit Armor(int v = 0) : value_(v > 0 ? v : 0) {}
    int reduceDamage(int damage) const {
        int result = damage - value_;
        return result > 0 ? result : 0;
    }
    int getValue() const { return value_; }
};