#include "Cliente.h"

Cliente::Cliente()
{
    //ctor
}

Cliente::~Cliente()
{
    //dtor
}

// Getters
int Cliente::getNumeroCedula() {
    return numeroCedula;
}

string Cliente::getNombre() {
    return nombre;
}

string Cliente::getApellido() {
    return apellido;
}
Mascota Cliente::getMascota() {
    return mascota;
}

// Setters
void Cliente::setNumeroCedula(int numeroCedula) {
    this->numeroCedula = numeroCedula;
}

void Cliente::setNombre(string nombre) {
    this->nombre = nombre;
}

void Cliente::setApellido(string apellido) {
    this->apellido = apellido;
}
void Cliente::setMascota(Mascota mascota) {
    this->mascota = mascota;
}
