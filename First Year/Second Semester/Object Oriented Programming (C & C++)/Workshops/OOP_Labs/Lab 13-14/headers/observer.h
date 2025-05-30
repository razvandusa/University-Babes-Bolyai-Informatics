#pragma once
#include <vector>

/**
 * Interfata Observer pentru implementarea modelului Observer.
 * Orice clasa derivata trebuie sa implementeze metoda update().
 */
class Observer {
public:
  /**
   * Metoda apelata atunci cand Subject-ul notifica observatorii.
   */
  virtual void update() = 0;
};

/**
 * Clasa Subject gestioneaza o lista de observatori si ii notifica atunci cand are loc o modificare.
 */
class Subject {
private:
  std::vector<Observer*> observers;

public:
  /**
   * Adauga un observator la lista.
   * @param observer Pointer catre observatorul care trebuie adaugat.
   */
  void addObserver(Observer* observer) {
    observers.push_back(observer);
  }

  /**
   * Elimina un observator din lista.
   * @param observer Pointer catre observatorul care trebuie eliminat.
   */
  void removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
  }

  /**
   * Notifica toti observatorii din lista prin apelarea metodei update().
   */
  void notifyObservers() {
    for (auto observer : observers) {
      observer->update();
    }
  }
};