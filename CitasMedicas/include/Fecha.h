#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Fecha
{
public:
    // Constructor
    Fecha();

    // Destructor
    virtual ~Fecha();

    // Getters
    int getDia();
    int getMes();
    int getAnio();

    // Setters
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    // Método para mostrar la fecha
    string toString();

    // Validar fecha
    bool esValida();

private:
    int dia;
    int mes;
    int anio;
};

#endif // FECHA_H
