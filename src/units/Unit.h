#pragma once
#include <string>
#include <memory>
#include "../attributes/Health.h"
#include "../attributes/Armor.h"
#include "../attributes/Attack.h"

class Unit {
protected:
    Health health_;
    Armor armor_;
    Attack attack_;
    int x_;
    int y_;

public:
    Unit(int hp, int armor, int atk)
        : health_(hp), armor_(armor), attack_(atk), x_(0), y_(0) {}

    virtual ~Unit() = default;

    virtual std::unique_ptr<Unit> clone() const = 0;
    virtual std::string getType() const = 0;
    virtual char getSymbol() const = 0;

    virtual void move(int newX, int newY) {
        x_ = newX;
        y_ = newY;
    }

    void attackUnit(Unit& target) {
        int dmg = attack_.calculateDamage(target.armor_);
        target.health_.decrease(dmg);
    }

    int getX() const { return x_; }
    int getY() const { return y_; }
    const Health& getHealth() const { return health_; }
    const Armor&  getArmor()  const { return armor_;  }
    const Attack& getAttack() const { return attack_; }
};