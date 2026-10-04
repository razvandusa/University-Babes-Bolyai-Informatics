#pragma once
#include <vector>

class Observer {
public:
    /**
     * Incrementeaza aparitia unui produs
     * @param tip tipul produsului pe care dorim sa il updatam
     */
    virtual void update(std::string tip) = 0;

    /**
     * Destructor default
     */
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    /**
     * Adauga un observer in lista de observers
     * @param observer observerul pe care il adaugam
     */
    void add_observer(Observer* observer) {
        observers.push_back(observer);
    }

    /**
     * Notifica toti observerii care au tipul precizat
     * @param tip tipul observerilor pe care dorim sa ii updatam
     */
    void notify_observers(std::string tip) {
        for (auto observer : observers) {
            observer->update(tip);
        }
    }
};