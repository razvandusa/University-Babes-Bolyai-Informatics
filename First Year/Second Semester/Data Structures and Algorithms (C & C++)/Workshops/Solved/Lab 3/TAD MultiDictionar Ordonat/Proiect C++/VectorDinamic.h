#pragma once
template <typename T>
class IteratorVectorDinamic;

template <typename T>
class VectorDinamic {
    private:
    T *elements;
    int dimensiune;
    int capacitate;
    public:
    template <typename U>
    friend class IteratorVectorDinamic;
    //Constructor
    VectorDinamic() {
        this->capacitate = 2;
        this->dimensiune = 0;
        elements = new T[capacitate];
    }

    //Constructor de copiere
    VectorDinamic(const VectorDinamic& other) {
        capacitate = other.capacitate;
        dimensiune = other.dimensiune;
        elements = new T[capacitate];
        for (int i = 0; i < dimensiune; ++i) {
            elements[i] = other.elements[i];
        }
    }

    //Destructor
    ~VectorDinamic() {
        delete[] elements;
    }

    //Operator de atribuire
    VectorDinamic& operator=(const VectorDinamic& other) {
        if (this != &other) {
            delete[] elements;
            capacitate = other.capacitate;
            dimensiune = other.dimensiune;
            elements = new T[capacitate];
            for (int i = 0; i < dimensiune; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    //Redimensionare
    void redimensionare() {
        int new_capacitate = this->capacitate * 2;
        T *new_elements = new T[new_capacitate];
        for (int i = 0; i < this->dimensiune; i++) {
            new_elements[i] = this->elements[i];
        }
        delete[] this->elements;
        this->elements = new_elements;
        this->capacitate = new_capacitate;
    }

    //Adaugare
    void adaugare(T element) {
        if (this->dimensiune == this->capacitate) {
            redimensionare();
        }
        this->elements[dimensiune++] = element;
    }

    //Dimensiune
    int dim() const{
        return this->dimensiune;
    }

    //Accesare element
    T& element(int index){
        return this->elements[index];
    }

    //Accesare element
    const T& element(int index) const {
        return elements[index];
    }

    //Stergere element
    void sterge(int index) {
        for (int i = index; i < dimensiune - 1; i++) {
            elements[i] = elements[i + 1];
        }
        dimensiune--;
    }

    //Inserare
    void inserare(int index, T element) {
        if (index < 0 || index > dimensiune) {
            throw std::out_of_range("Index invalid la inserare");
        }
        if (dimensiune == capacitate) {
            redimensionare();
        }
        for (int i = dimensiune; i > index; i--) {
            elements[i] = elements[i - 1];
        }
        elements[index] = element;
        dimensiune++;
    }


    //Returneaza iterator pe vector
    IteratorVectorDinamic<T> iterator() const{
        return IteratorVectorDinamic(*this);
    }
};

template <typename T>
class IteratorVectorDinamic {
private:
    //Referinta la vectorul pe care il itereaza
    const VectorDinamic<T>& v;
    //Pozitia curenta in iterator
    int curent;
public:
    //Constructor
    IteratorVectorDinamic(const VectorDinamic<T>& referinta) : v(referinta) {
        curent = 0;
    }
    //Operatii pe iterator
    void prim() {
        curent = 0;
    }
    void urmator() {
        curent++;
    }
    bool valid() const {
        return curent < v.dim();
    }
    T element() const {
        return v.element(curent);
    }
};