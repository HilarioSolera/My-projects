#ifndef DOCTOR_H
#define DOCTOR_H
#include <string>
#include <iostream>
using namespace std;


class Doctor
{
    public:
        Doctor();
        virtual ~Doctor();
        /*setters*/
       int getNumeroCedula();
       string getNombre();
       string getApellido();
       string getEspecialidad();
       /*Getters*/
    void setNumeroCedula(int numeroCedula);
    void setNombre(string nombre);
    void setApellido(string apellido);
    void setEspecialidad(string especialidad);


    protected:

    private:
        /*atributos*/
      int numeroCedula;
      string nombre;
      string apellido;
      string especialidad;
};

#endif // DOCTOR_H
