#ifndef MASCOTA_H
#define MASCOTA_H
#include <string>
#include <iostream>
using namespace std;


class Mascota
{
    public:
        Mascota();
        virtual ~Mascota();
        // Getters
    string getNombre();
    string getTipo();
    string getRaza();
    double getPeso();
    int getEdad();

    // Setters
    void setNombre(string nombre);
    void setTipo(string tipo);
    void setRaza(string raza);
    void setPeso(double peso);
    void setEdad(int edad);


    protected:

    private:
        string nombre;
        string tipo;
        string raza;
        double peso;
        int edad;
};

#endif // MASCOTA_H
