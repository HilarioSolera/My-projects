#ifndef CITA_H
#define CITA_H

#include "Cliente.h"
#include "Doctor.h"
#include "Hora.h"
#include <string>

using namespace std;

class Cita
{
public:
    Cita();
    virtual ~Cita();

    // Getters
    int getCodigo();
    Cliente getCliente();
    Doctor getDoctor();
    string getDia();
    Hora getHora();
    string getObservacion();

    // Setters
    void setCodigo(int codigo);
    void setCliente(Cliente cliente);
    void setDoctor(Doctor doctor);
    void setDia(string dia);
    void setHora(Hora hora);
    void setObservacion(string observacion);

private:
    int codigo;
    Cliente cliente;
    Doctor doctor;
    string dia;
    Hora hora;
    string observacion;
};

#endif // CITA_H
