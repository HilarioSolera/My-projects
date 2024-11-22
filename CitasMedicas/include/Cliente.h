#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include <iostream>
#include "Mascota.h"
using namespace std;



class Cliente
{
    public:
        Cliente();
        virtual ~Cliente();
        /*getter*/
        int getNumeroCedula();
        string getNombre();
        string getApellido();
        Mascota getMascota();
        /*setter*/
        void setNumeroCedula(int numeroCedula);
        void setNombre(string nombre);
        void setApellido(string apellido);
        void setMascota(Mascota mascota);

    protected:

    private:
/*atributos*/
    int numeroCedula;
    string nombre;
    string apellido;
     Mascota mascota;

};

#endif // CLIENTE_H
