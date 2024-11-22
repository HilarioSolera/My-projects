#include "Doctor.h"

Doctor::Doctor()
{
    //ctor
}

Doctor::~Doctor()
{
    //dtor
}

// Getters
int Doctor::getNumeroCedula() {
    return numeroCedula;
}

string Doctor::getNombre() {
    return nombre;
}

string Doctor::getApellido() {
    return apellido;
}

string Doctor::getEspecialidad() {
    return especialidad;
}

// Setters
void Doctor::setNumeroCedula(int numeroCedula) {
    this->numeroCedula = numeroCedula;
}

void Doctor::setNombre(string nombre) {
    this->nombre = nombre;
}

void Doctor::setApellido(string apellido) {
    this->apellido = apellido;
}

void Doctor::setEspecialidad(string especialidad) {
    this->especialidad = especialidad;
}
