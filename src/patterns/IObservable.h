#pragma once
#include <vector>
#include <algorithm>
#include "IObserver.h"

class IObservable {
protected:
    std::vector<IObserver*> observers_;

public:
    virtual ~IObservable() = default;

    void subscribe(IObserver* observer) {
        observers_.push_back(observer);
    }

    void unsubscribe(IObserver* observer) {
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer), 
            observers_.end()
        );
    }

protected:
    void notify(const UnitEvent& event) {
        for (auto* obs : observers_) {
            obs->onUnitEvent(event);
        }
    }
};