// #include "VectorDinamic.h"
//
// VectorDinamic::VectorDinamic(int capacitate) {
//     this->capacitate = capacitate;
//     this->dimensiune = 0;
//     elements = new int[capacitate];
// }
//
// VectorDinamic::~VectorDinamic() {
//     delete[] elements;
// }
//
// void VectorDinamic::redimensionare() {
//     int new_capacitate = this->capacitate * 2;
//     int *new_elements = new int[new_capacitate];
//     for (int i = 0; i < this->dimensiune; i++) {
//         new_elements[i] = this->elements[i];
//     }
//     delete[] this->elements;
//     this->elements = new_elements;
//     this->capacitate = new_capacitate;
// }
//
// void VectorDinamic::adaugare(int element) {
//     if (this->dimensiune == this->capacitate) {
//         redimensionare();
//     }
//     this->elements[dimensiune++] = element;
// }
//
// int VectorDinamic::dim() {
//     return this->dimensiune;
// }
//
// int VectorDinamic::element(int index) {
//     return this->elements[index];
// }
//
// IteratorVectorDinamic VectorDinamic::iterator() {
//     return IteratorVectorDinamic(*this);
// }
//
// IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic &referinta) : v(referinta) {
//     curent = 0;
// }
//
// void IteratorVectorDinamic::prim() {
//     curent = 0;
// }
//
// void IteratorVectorDinamic::urmator() {
//     curent++;
// }
//
// bool IteratorVectorDinamic::valid() const {
//     return curent < v.dimensiune;
// }
//
// int IteratorVectorDinamic::element() const{
//     return v.elements[curent];
// }