#pragma once

enum class EventType {
    Created,
    Healed,
    Damaged,
    Destroyed
};

struct UnitEvent {
    EventType type;
    int unit_id;
    int damage;
    
    UnitEvent(EventType t, int id, int dmg = 0) 
        : type(t), unit_id(id), damage(dmg) {}
};