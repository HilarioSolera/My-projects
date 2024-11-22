#include "Mascota.h"

Mascota::Mascota()
{
    //ctor
}

Mascota::~Mascota()
{
    //dtor
}

// Getters
string Mascota::getNombre() {
    return nombre;
}

string Mascota::getTipo() {
    return tipo;
}

string Mascota::getRaza() {
    return raza;
}

double Mascota::getPeso() {
    return peso;
}

int Mascota::getEdad() {
    return edad;
}

// Setters
void Mascota::setNombre(string nombre) {
    this->nombre = nombre;
}

void Mascota::setTipo(string tipo) {
    this->tipo = tipo;
}

void Mascota::setRaza(string raza) {
    this->raza = raza;
}

void Mascota::setPeso(double peso) {
    this->peso = peso;
}

void Mascota::setEdad(int edad) {
    this->edad = edad;
}
