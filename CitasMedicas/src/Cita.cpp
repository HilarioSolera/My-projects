#include "Cita.h"

// Constructor

Cita::Cita(){

}

// Destructor
Cita::~Cita()
{
}
// Getters
int Cita::getCodigo() {
    return codigo;
}

Cliente Cita::getCliente() {
    return cliente;
}

Doctor Cita::getDoctor() {
    return doctor;
}

string Cita::getDia() {
    return dia;
}

Hora Cita::getHora() {
    return hora;
}

string Cita::getObservacion() {
    return observacion;
}

// Setters
void Cita::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Cita::setCliente(Cliente cliente) {
    this->cliente = cliente;
}

void Cita::setDoctor(Doctor doctor) {
    this->doctor = doctor;
}

void Cita::setDia(string dia) {
    this->dia = dia;
}

void Cita::setHora(Hora hora) {
    this->hora = hora;
}

void Cita::setObservacion(string observacion) {
    this->observacion = observacion;
}
