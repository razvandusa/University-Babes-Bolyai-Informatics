#pragma once
#include <vector>

class Observer {
public:
    virtual void update() = 0;

    virtual ~Observer() = default;
};

class Subject {
    public:
        void add_observer(Observer* observer) {
            observers.push_back(observer);
        }

        void notify_observers() {
            for (auto& observer : observers) {
                observer->update();
            }
        }
private:
    std::vector<Observer*> observers;
};