#ifndef HORA_H
#define HORA_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Hora
{
public:
    // Constructor
    Hora();

    // Destructor
    virtual ~Hora();

    // Getters
    int getHora();
    int getMinuto();
    string getPeriodo();

    // Setters
    void setHora(int hora);
    void setMinuto(int minuto);
    void setPeriodo(string periodo);



private:
    /*atributos*/
    int hora;
    int minuto;


};

#endif // HORA_H
