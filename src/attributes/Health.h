#pragma once

class Health {
private:
    int value_;
public:
    explicit Health(int v = 0) : value_(v > 0 ? v : 0) {}

    void decrease(int amount) {
        if (amount < 0) return;
        value_ -= amount;
        if (value_ < 0) value_ = 0;
    }
    void increase(int amount) {
        if (amount < 0) return;
        value_ += amount;
    }
    bool isZero() const { return value_ == 0; }
    int getValue() const { return value_; }
};