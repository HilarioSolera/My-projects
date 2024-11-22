#include "Fecha.h"

// Constructor
Fecha::Fecha() {
}

// Destructor
Fecha::~Fecha() {
}

// Getters
int Fecha::getDia() {
    return dia;
}

int Fecha::getMes() {
    return mes;
}

int Fecha::getAnio() {
    return anio;
}

// Setters
void Fecha::setDia(int dia) {
    this->dia = dia;
}

void Fecha::setMes(int mes) {
    this->mes = mes;
}

void Fecha::setAnio(int anio) {
    this->anio = anio;
}

// Método para mostrar la fecha
string Fecha::toString() {
    ostringstream oss;
    oss << setw(2) << setfill('0') << dia << "/"
        << setw(2) << setfill('0') << mes << "/"
        << anio;
    return oss.str();
}

// Validar fecha
bool Fecha::esValida() {
    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return false;
    }

    // Verificar días en febrero
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if ((esBisiesto && dia > 29) || (!esBisiesto && dia > 28)) {
            return false;
        }
    }

    // Verificar días en meses con 30 días
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return false;
    }

    return true;
}
