//21-07-2024
//HILARIO DAVID SOLERA MEZA

#include <iostream> // Biblioteca estándar para la entrada y salida de datos
#include <vector>   // Biblioteca estándar para utilizar la plantilla de contenedores vector
#include "Cliente.h"  // Incluir la definición de la clase Cliente
#include "Doctor.h"   // Incluir la definición de la clase Doctor
#include "Mascota.h"  // Incluir la definición de la clase Mascota
#include "Fecha.h"    // Incluir la definición de la clase Fecha
#include "Hora.h"     // Incluir la definición de la clase Hora
#include "Cita.h"     // Incluir la definición de la clase Cita
#include <fstream>    // Biblioteca estándar para operaciones con archivos
#include <cstdlib>    // Biblioteca estándar para funciones de propósito general como exit()
#include <limits>     // Biblioteca estándar para obtener límites de tipos de datos
#include <algorithm>  // Biblioteca estándar para funciones de algoritmos como sort()
#include <Windows.h> // Biblioteca estándar para funciones de la consola

using namespace std; // Usar el espacio de nombres estándar para evitar la necesidad de anteponer "std::" a los nombres de las funciones y tipos de datos

vector<Doctor> doctores; /* vector para almacenar una lista de objetos Doctor.*/

vector<Cliente> clientes; /* vector para almacenar una lista de objetos Cliente.*/

vector<Cita> citas; /* vector para almacenar una lista de objetos Cita.*/


void leerClientes() {
    // Abre el archivo "CLIENTES.TXT" en modo lectura
    ifstream archivo("CLIENTES.TXT");

    // Verifica si el archivo no se pudo abrir
    if (!archivo.is_open()) {
        cout << "Error al abrir CLIENTES.TXT" << endl; // Muestra un mensaje de error si el archivo no se puede abrir.
        return;  // Sale de la función si no se puede abrir el archivo.
    }

    // Limpia el vector de clientes antes de cargar nuevos datos
    clientes.clear();  // Asegura que el vector esté vacío antes de agregar nuevos datos para evitar datos antiguos.

    string linea;  // Variable para almacenar cada línea leída del archivo.
    // Lee el archivo línea por línea
    while (getline(archivo, linea)) {  // Lee cada línea del archivo CLIENTES.TXT.
        // Crea un stringstream a partir de la línea leída
        stringstream ss(linea);  // Usa un `stringstream` para procesar la línea leída del archivo.
        string campo;  // Variable para almacenar los campos separados por el delimitador.

        Cliente cliente;  // Crea un objeto `Cliente` para almacenar la información de cada cliente leída.
        Mascota mascota;  // Crea un objeto `Mascota` para almacenar la información de la mascota.

        // Lee y establece el número de cédula del cliente desde el archivo
        getline(ss, campo, ',');  // Lee hasta el delimitador ',' que separa los campos en la línea del archivo.
        cliente.setNumeroCedula(stoi(campo));  // Convierte el campo leído (cédula del cliente) de cadena a entero y lo establece en el objeto `Cliente`.

        // Lee y establece el nombre del cliente desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        cliente.setNombre(campo);  // Establece el nombre del cliente en el objeto `Cliente`.

        // Lee y establece el apellido del cliente desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        cliente.setApellido(campo);  // Establece el apellido del cliente en el objeto `Cliente`.

        // Lee y establece el nombre de la mascota del cliente desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        mascota.setNombre(campo);  // Establece el nombre de la mascota en el objeto `Mascota`.

        // Lee y establece el tipo de mascota desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        mascota.setTipo(campo);  // Establece el tipo de la mascota en el objeto `Mascota`.

        // Lee y establece la raza de la mascota desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        mascota.setRaza(campo);  // Establece la raza de la mascota en el objeto `Mascota`.

        // Lee y establece el peso de la mascota desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        mascota.setPeso(stod(campo));  // Convierte el campo leído (peso de la mascota) de cadena a `double` y lo establece en el objeto `Mascota`.

        // Lee y establece la edad de la mascota desde el archivo
        getline(ss, campo);  // Lee el resto de la línea como la edad de la mascota.
        mascota.setEdad(stoi(campo));  // Convierte el campo leído (edad de la mascota) de cadena a entero y lo establece en el objeto `Mascota`.

        // Asigna la mascota al cliente
        cliente.setMascota(mascota);  // Asigna el objeto `Mascota` al objeto `Cliente`.

        // Añade el objeto cliente al vector de clientes
        clientes.push_back(cliente);  // Agrega el objeto `Cliente` al vector `clientes`.
    }

    // Cierra el archivo
    archivo.close();  // Cierra el archivo después de leer todos los datos.
}

void leerDoctores() {
    // Abre el archivo "DOCTORES.TXT" en modo lectura
    ifstream archivo("DOCTORES.TXT");

    // Verifica si el archivo no se pudo abrir
    if (!archivo.is_open()) {
        cout << "Error al abrir DOCTORES.TXT" << endl;  // Muestra un mensaje de error si el archivo no se puede abrir.
        return;  // Sale de la función si no se puede abrir el archivo.
    }

    // Limpia el vector de doctores antes de cargar nuevos datos
    doctores.clear();  // Asegura que el vector esté vacío antes de agregar nuevos datos para evitar datos antiguos.

    string linea;  // Variable para almacenar cada línea leída del archivo.
    // Lee el archivo línea por línea
    while (getline(archivo, linea)) {  // Lee cada línea del archivo DOCTORES.TXT.
        // Crea un stringstream a partir de la línea leída
        stringstream ss(linea);  // Usa un `stringstream` para procesar la línea leída del archivo.
        string campo;  // Variable para almacenar los campos separados por el delimitador.

        Doctor doctor;  // Crea un objeto `Doctor` para almacenar la información de cada doctor leída.

        // Lee y establece el número de cédula del doctor desde el archivo
        getline(ss, campo, ',');  // Lee hasta el delimitador ',' que separa los campos en la línea del archivo.
        doctor.setNumeroCedula(stoi(campo));  // Convierte el campo leído (cédula del doctor) de cadena a entero y lo establece en el objeto `Doctor`.

        // Lee y establece el nombre del doctor desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        doctor.setNombre(campo);  // Establece el nombre del doctor en el objeto `Doctor`.

        // Lee y establece el apellido del doctor desde el archivo
        getline(ss, campo, ',');  // Lee el siguiente campo hasta el delimitador ','.
        doctor.setApellido(campo);  // Establece el apellido del doctor en el objeto `Doctor`.

        // Lee y establece la especialidad del doctor desde el archivo
        getline(ss, campo);  // Lee el resto de la línea como la especialidad del doctor.
        doctor.setEspecialidad(campo);  // Establece la especialidad del doctor en el objeto `Doctor`.

        // Añade el objeto doctor al vector de doctores
        doctores.push_back(doctor);  // Agrega el objeto `Doctor` al vector `doctores`.
    }

    // Cierra el archivo
    archivo.close();  // Cierra el archivo después de leer todos los datos.
}

void leerCitas() {
    ifstream archivo("CITAS.TXT"); // Abre el archivo CITAS.TXT en modo de lectura.
    if (!archivo.is_open()) { // Verifica si el archivo se ha abierto correctamente.
        cout << "Error al abrir CITAS.TXT" << endl; // Muestra un mensaje de error si el archivo no se puede abrir.
        return; // Sale de la función si no se puede abrir el archivo.
    }

    citas.clear(); // Limpia el vector de citas antes de cargar nuevos datos para evitar duplicados.

    string linea; // Variable para almacenar cada línea leída del archivo.
    while (getline(archivo, linea)) { // Lee cada línea del archivo CITAS.TXT.
        stringstream ss(linea); // Crea un `stringstream` para procesar la línea leída del archivo.
        string campo; // Variable para almacenar los campos separados por el delimitador.

        Cita cita; // Crea un objeto `Cita` para almacenar la información de cada cita leída.

        // Lee y establece el código de la cita desde el archivo.
        getline(ss, campo, '|'); // Lee hasta el delimitador '|', que separa los campos en la línea del archivo.
        int codigoCita = stoi(campo); // Convierte el campo leído (código de cita) de cadena a entero.
        cita.setCodigo(codigoCita); // Asigna el código de la cita al objeto `Cita`.

        // Lee y obtiene la cédula del cliente desde el archivo.
        getline(ss, campo, '|'); // Lee el siguiente campo hasta el delimitador '|'.
        int cedulaCliente = stoi(campo); // Convierte el campo leído (cédula del cliente) de cadena a entero.

        // Busca y asigna el cliente correspondiente a la cita.
        Cliente clienteEncontrado; // Crea un objeto `Cliente` para almacenar el cliente encontrado.
        bool clienteExiste = false; // Variable para verificar si el cliente existe.
        for (int i = 0; i < clientes.size(); i++) { // Itera sobre todos los clientes en el vector `clientes`.
            if (clientes[i].getNumeroCedula() == cedulaCliente) { // Compara la cédula del cliente con el ID leído del archivo.
                clienteEncontrado = clientes[i]; // Asigna el cliente encontrado al objeto `clienteEncontrado`.
                clienteExiste = true; // Marca que el cliente ha sido encontrado.
                break; // Sale del bucle ya que no es necesario buscar más.
            }
        }
        if (!clienteExiste) { // Si el cliente no se encuentra en el vector de clientes.
            cout << "Cliente con cédula " << cedulaCliente << " no encontrado." << endl; // Muestra un mensaje indicando que el cliente no existe.
            continue; // Pasa al siguiente registro en el archivo, ignorando la cita actual.
        }
        cita.setCliente(clienteEncontrado); // Asigna el cliente encontrado a la cita.

        // Lee y obtiene la cédula del doctor desde el archivo.
        getline(ss, campo, '|'); // Lee el siguiente campo hasta el delimitador '|'.
        int cedulaDoctor = stoi(campo); // Convierte el campo leído (cédula del doctor) de cadena a entero.

        // Busca y asigna el doctor correspondiente a la cita.
        Doctor doctorEncontrado; // Crea un objeto `Doctor` para almacenar el doctor encontrado.
        bool doctorExiste = false; // Variable para verificar si el doctor existe.
        for (int j = 0; j < doctores.size(); j++) { // Itera sobre todos los doctores en el vector `doctores`.
            if (doctores[j].getNumeroCedula() == cedulaDoctor) { // Compara la cédula del doctor con el ID leído del archivo.
                doctorEncontrado = doctores[j]; // Asigna el doctor encontrado al objeto `doctorEncontrado`.
                doctorExiste = true; // Marca que el doctor ha sido encontrado.
                break; // Sale del bucle ya que no es necesario buscar más.
            }
        }
        if (!doctorExiste) { // Si el doctor no se encuentra en el vector de doctores.
            cout << "Doctor con cédula " << cedulaDoctor << " no encontrado." << endl; // Muestra un mensaje indicando que el doctor no existe.
            continue; // Pasa al siguiente registro en el archivo, ignorando la cita actual.
        }
        cita.setDoctor(doctorEncontrado); // Asigna el doctor encontrado a la cita.

        // Lee y obtiene el día de la cita desde el archivo.
        getline(ss, campo, '|'); // Lee el siguiente campo hasta el delimitador '|'.
        cita.setDia(campo); // Asigna el día de la cita al objeto `Cita`. (El campo ya es una cadena con el nombre del día)

        // Lee y obtiene la hora desde el archivo.
        getline(ss, campo, '|'); // Lee el siguiente campo hasta el delimitador '|'.
        int horas, minutos; // Variables para almacenar las horas y minutos de la cita.
        stringstream horaStream(campo); // Crea un `stringstream` para procesar el campo de la hora.
        char separadorHora; // Variable para almacenar el separador ':' en el formato de hora.
        horaStream >> horas >> separadorHora >> minutos; // Extrae las horas y minutos del campo de hora.
        Hora hora; // Crea un objeto `Hora` para almacenar la hora de la cita.
        hora.setHora(horas); // Establece las horas en el objeto `Hora`.
        hora.setMinuto(minutos); // Establece los minutos en el objeto `Hora`.
        cita.setHora(hora); // Asigna la hora de la cita al objeto `Cita`.

        // Lee y establece la observación desde el archivo.
        getline(ss, campo); // Lee el resto de la línea como la observación de la cita.
        cita.setObservacion(campo); // Establece la observación en el objeto `Cita`.

        // Añade el objeto `Cita` al vector de citas.
        citas.push_back(cita); // Agrega el objeto `Cita` al vector `citas`.
    }

    archivo.close(); // Cierra el archivo después de leer todos los datos.
}

bool validarCedula(const string& cedula) {
    // Retorna true si la cédula tiene exactamente 9 caracteres y todos son dígitos; de lo contrario, retorna false.

    // Verifica que la longitud de la cédula sea exactamente 9 caracteres.
    // La función `length()` obtiene el número de caracteres en el string.
    // La comparación `== 9` asegura que solo cédulas con 9 caracteres sean consideradas válidas.
    // `cedula.length() == 9` verifica la longitud de la cédula.

    // La función `all_of` verifica que todos los caracteres en el rango especificado cumplan con una condición.
    // `cedula.begin()` y `cedula.end()` especifican el rango completo del string `cedula` para la verificación.
    // `::isdigit` es una función que verifica si un carácter es un dígito.
    // `all_of(cedula.begin(), cedula.end(), ::isdigit)` verifica que todos los caracteres en `cedula` sean dígitos.
    // Si todos los caracteres son dígitos y la longitud es 9, `validarCedula` devuelve `true`, de lo contrario, devuelve `false`.

    // Devuelve verdadero si la cédula es válida (exactamente 9 dígitos), de lo contrario, falso.
    return cedula.length() == 9 && all_of(cedula.begin(), cedula.end(), ::isdigit);
}

// Esta función muestra un mensaje de error en la consola y luego espera a que el usuario presione una tecla para continuar.
void mostrarError(const string& mensaje) {
    // Limpia la pantalla de la consola (solo en sistemas Windows). Borra todo el contenido mostrado en la ventana de la consola.
    system("cls");

    // Muestra el mensaje de error proporcionado como argumento en la consola.
    cout << mensaje << endl;

    // Pausa la ejecución del programa y espera a que el usuario presione una tecla para continuar (solo en sistemas Windows).
    system("pause");
}


bool soloLetras(const string& letra, size_t index = 0) {
    // Caso base: Si hemos llegado al final de la cadena, todas las letras han sido validadas.
    if (index == letra.length()) {
        return true;
    }

    // Verificar si el carácter actual es una letra.
    if (!isalpha(letra[index])) {
        return false;
    }

    // Llamada recursiva con el siguiente carácter.
    return soloLetras(letra, index + 1);
}

bool soloDigitos(const string& numero, size_t index = 0) {
    // Caso base: Si hemos recorrido toda la cadena
    if (index == numero.length()) {
        return true;
    }
    // Verificar si el carácter actual es un dígito
    if (!isdigit(numero[index])) {
        return false;
    }
    // Llamada recursiva para el siguiente carácter
    return soloDigitos(numero, index + 1);
}

void ingresarCliente() {
    system("cls"); // Limpia la pantalla para que el usuario vea la información actualizada.

    Cliente* cliente = new Cliente(); // Crea un nuevo objeto `Cliente` dinámicamente en memoria.
    Mascota* mascota = new Mascota(); // Crea un nuevo objeto `Mascota` dinámicamente en memoria.

    string cedulaOpcional; // Variable para almacenar la cédula como una cadena de caracteres.
    string nombre, apellido, nombreMascota, raza; // Variables para almacenar el nombre del cliente, apellido, nombre de la mascota, y raza.
    string pesoStr, edadStr; // Variables temporales para almacenar el peso y la edad como cadenas de texto.
    double peso; // Variable para almacenar el peso de la mascota como un número real.
    int edad, tipoMascotaNum; // Variables para almacenar la edad de la mascota como un entero y el tipo de mascota como número.

    // Solicita al usuario que ingrese la cédula del cliente y verifica que sea válida.
    cout << "Ingrese numero de cedula (exactamente 9 digitos): ";
    cin >> cedulaOpcional; // Lee la cédula ingresada por el usuario.
    // Verifica que la cédula tenga exactamente 9 dígitos y que todos sean números.
    while (cedulaOpcional.length() != 9 || !soloDigitos(cedulaOpcional)) {
        system("cls"); // Limpia la pantalla si la cédula es inválida.
        cout << "Cedula invalida. Ingrese nuevamente (exactamente 9 digitos): ";
        cin >> cedulaOpcional; // Solicita al usuario que ingrese nuevamente la cédula.
    }
    int cedula = stoi(cedulaOpcional); // Convierte la cédula de cadena a entero.
    cliente->setNumeroCedula(cedula); // Asigna el número de cédula al objeto `Cliente`.

    // Verifica si ya existe un cliente con esa cédula en la lista de clientes.
    for (int i = 0; i < clientes.size(); ++i) {
        if (clientes[i].getNumeroCedula() == cedula) {
            cout << "El cliente ya esta registrado." << endl; // Muestra mensaje si el cliente ya está registrado.
            delete cliente; // Libera la memoria asignada al objeto `Cliente`.
            delete mascota; // Libera la memoria asignada al objeto `Mascota`.
            system("pause"); // Pausa el programa para que el usuario pueda ver el mensaje.
            return; // Sale de la función ya que el cliente ya está registrado.
        }
    }

    // Solicita al usuario que ingrese el nombre del cliente.
    system("cls"); // Limpia la pantalla.
    cout << "Ingrese nombre: ";
    cin >> nombre; // Lee el nombre del cliente.
    // Verifica que el nombre contenga solo letras.
    while (!soloLetras(nombre)) {
        system("cls"); // Limpia la pantalla si el nombre es inválido.
        cout << "Nombre invalido. Ingrese nuevamente: ";
        cin >> nombre; // Solicita al usuario que ingrese un nombre válido.
    }
    cliente->setNombre(nombre); // Asigna el nombre al objeto `Cliente`.

    // Solicita al usuario que ingrese el apellido del cliente.
    system("cls"); // Limpia la pantalla.
    cout << "Ingrese apellido: ";
    cin >> apellido; // Lee el apellido del cliente.
    // Verifica que el apellido contenga solo letras.
    while (!soloLetras(apellido)) {
        system("cls"); // Limpia la pantalla si el apellido es inválido.
        cout << "Apellido invalido. Ingrese nuevamente: ";
        cin >> apellido; // Solicita al usuario que ingrese un apellido válido.
    }
    cliente->setApellido(apellido); // Asigna el apellido al objeto `Cliente`.

    // Solicita al usuario que ingrese el nombre de la mascota.
    system("cls"); // Limpia la pantalla.
    cout << "Ingrese nombre de la mascota: ";
    cin >> nombreMascota; // Lee el nombre de la mascota.
    // Verifica que el nombre de la mascota contenga solo letras.
    while (!soloLetras(nombreMascota)) {
        system("cls"); // Limpia la pantalla si el nombre de la mascota es inválido.
        cout << "Nombre de mascota invalido. Ingrese nuevamente: ";
        cin >> nombreMascota; // Solicita al usuario que ingrese un nombre de mascota válido.
    }
    mascota->setNombre(nombreMascota); // Asigna el nombre de la mascota al objeto `Mascota`.

    // Solicita al usuario que seleccione el tipo de mascota (gato o perro).
    system("cls"); // Limpia la pantalla.
    cout << "Seleccione tipo de mascota:" << endl;
    cout << "1. Gato" << endl;
    cout << "2. Perro" << endl;
    cin >> tipoMascotaNum; // Lee la selección del tipo de mascota.
    // Verifica que la selección sea válida (1 para gato, 2 para perro).
    while (cin.fail() || (tipoMascotaNum != 1 && tipoMascotaNum != 2)) {
        cin.clear(); // Limpia el estado de error del flujo de entrada.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora los caracteres inválidos en el buffer de entrada.
        system("cls"); // Limpia la pantalla.
        cout << "Tipo invalido. Ingrese nuevamente (1 para gato, 2 para perro): ";
        cin >> tipoMascotaNum; // Solicita al usuario que ingrese una opción válida.
    }
    // Asigna el tipo de mascota al objeto `Mascota`.
    mascota->setTipo((tipoMascotaNum == 1) ? "gato" : "perro");

    // Solicita al usuario que ingrese la raza de la mascota.
    system("cls"); // Limpia la pantalla.
    cout << "Ingrese raza: ";
    cin >> raza; // Lee la raza de la mascota.
    // Verifica que la raza contenga solo letras.
    while (!soloLetras(raza)) {
        system("cls"); // Limpia la pantalla si la raza es inválida.
        cout << "Raza invalida. Ingrese nuevamente: ";
        cin >> raza; // Solicita al usuario que ingrese una raza válida.
    }
    mascota->setRaza(raza); // Asigna la raza de la mascota al objeto `Mascota`.

    // Solicita al usuario que ingrese el peso de la mascota.
    system("cls"); // Limpia la pantalla.
    cout << "Ingrese peso: ";
    cin >> pesoStr; // Lee el peso de la mascota como una cadena de texto.
    // Verifica que el peso sea un número válido en el rango de 1 a 100 kg.
    while (cin.fail() || !soloDigitos(pesoStr) || (peso = stod(pesoStr)) <= 0 || peso > 100) {
        cin.clear(); // Limpia el estado de error del flujo de entrada.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora los caracteres inválidos en el buffer de entrada.
        system("cls"); // Limpia la pantalla.
        cout << "Valor del peso fuera de rango (1-100 kg): ";
        cin >> pesoStr; // Solicita al usuario que ingrese un peso válido.
    }
    mascota->setPeso(peso); // Asigna el peso de la mascota al objeto `Mascota`.

    // Solicita al usuario que ingrese la edad de la mascota.
    system("cls"); // Limpia la pantalla.
    cout << "Ingrese edad de la mascota: ";
    cin >> edadStr; // Lee la edad de la mascota como una cadena de texto.
    // Verifica que la edad sea un número válido en el rango de 0 a 30 años.
    while (cin.fail() || !soloDigitos(edadStr) || (edad = stoi(edadStr)) < 0 || edad > 30) {
        cin.clear(); // Limpia el estado de error del flujo de entrada.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora los caracteres inválidos en el buffer de entrada.
        system("cls"); // Limpia la pantalla.
        cout << "Valor de edad fuera de rango” (0-30 años): ";
        cin >> edadStr; // Solicita al usuario que ingrese una edad válida.
    }
    mascota->setEdad(edad); // Asigna la edad de la mascota al objeto `Mascota`.

    cliente->setMascota(*mascota); // Asigna el objeto `Mascota` al objeto `Cliente`.
    clientes.push_back(*cliente); // Agrega el objeto `Cliente` a la lista de clientes.

    // Abre el archivo CLIENTES.TXT en modo de añadir (append) para agregar los datos del nuevo cliente.
    ofstream archivo("CLIENTES.TXT", ios::app);
    if (archivo.is_open()) { // Verifica si el archivo se ha abierto correctamente.
        // Escribe los datos del cliente en el archivo separados por comas.
        archivo << cedula << "," << nombre << "," << apellido << ","
                << nombreMascota << "," << mascota->getTipo() << ","
                << raza << "," << peso << "," << edad << endl;
        archivo.close(); // Cierra el archivo después de escribir los datos.
        cout << "Cliente registrado con exito." << endl; // Muestra un mensaje de éxito.
    } else {
        cout << "No se pudo abrir el archivo CLIENTES.TXT para guardar el cliente." << endl; // Muestra un mensaje de error si el archivo no se abre.
    }

    delete cliente; // Libera la memoria asignada al objeto `Cliente`.
    delete mascota; // Libera la memoria asignada al objeto `Mascota`.
}

void ingresarDoctor() {
    system("cls"); // Limpia la pantalla para que el usuario vea la información actualizada.

    Doctor* doctor = new Doctor(); // Crea un nuevo objeto `Doctor` dinámicamente en memoria.

    string cedulaOpcional; // Variable para almacenar la cédula del doctor como una cadena de caracteres.
    int cedula; // Variable para almacenar la cédula del doctor como un entero.
    string nombre, apellido, especialidad; // Variables para almacenar el nombre, apellido y especialidad del doctor.
    int opcion; // Variable para almacenar la opción de especialidad seleccionada por el usuario.

    // Solicita al usuario que ingrese la cédula del doctor.
    cout << "Ingrese numero de cedula (exactamente 9 digitos): ";
    cin >> cedulaOpcional; // Lee la cédula ingresada por el usuario.
    system("cls"); // Limpia la pantalla después de ingresar la cédula.

    // Verifica que la cédula tenga exactamente 9 dígitos y que todos sean números.
    while (cedulaOpcional.length() != 9 || !soloDigitos(cedulaOpcional)) {
        cout << "Cedula invalida. Ingrese nuevamente (exactamente 9 digitos): ";
        cin >> cedulaOpcional; // Solicita al usuario que ingrese una cédula válida.
        system("cls"); // Limpia la pantalla si la cédula es inválida.
    }

    try {
        cedula = stoi(cedulaOpcional); // Convierte la cédula de cadena a entero.
    } catch (const invalid_argument&) {
        cout << "Error: La cédula debe ser un número entero válido." << endl; // Muestra un mensaje de error si la conversión falla.
        delete doctor; // Libera la memoria asignada al objeto `Doctor` en caso de error.
        return; // Sale de la función si la conversión de cédula falla.
    }

    // Verifica si ya existe un doctor con ese ID en la lista de doctores.
    for (int i = 0; i < doctores.size(); ++i) {
        if (doctores[i].getNumeroCedula() == cedula) {
            cout << "El doctor ya esta registrado." << endl; // Muestra un mensaje si el doctor ya está registrado.
            delete doctor; // Libera la memoria asignada al objeto `Doctor`.
            system("pause"); // Pausa el programa para que el usuario pueda ver el mensaje.
            return; // Sale de la función si el doctor ya está registrado.
        }
    }

    doctor->setNumeroCedula(cedula); // Asigna el número de cédula al objeto `Doctor`.

    // Solicita al usuario que ingrese el nombre del doctor.
    cout << "Ingrese nombre: ";
    cin >> nombre; // Lee el nombre del doctor.
    system("cls"); // Limpia la pantalla después de ingresar el nombre.

    // Verifica que el nombre del doctor contenga solo letras.
    while (!soloLetras(nombre)) {
        cout << "Nombre invalido. Ingrese nuevamente: ";
        cin >> nombre; // Solicita al usuario que ingrese un nombre válido.
        system("cls"); // Limpia la pantalla si el nombre es inválido.
    }
    doctor->setNombre(nombre); // Asigna el nombre al objeto `Doctor`.

    // Solicita al usuario que ingrese el apellido del doctor.
    cout << "Ingrese apellido: ";
    cin >> apellido; // Lee el apellido del doctor.
    system("cls"); // Limpia la pantalla después de ingresar el apellido.

    // Verifica que el apellido del doctor contenga solo letras.
    while (!soloLetras(apellido)) {
        cout << "Apellido invalido. Ingrese nuevamente: ";
        cin >> apellido; // Solicita al usuario que ingrese un apellido válido.
        system("cls"); // Limpia la pantalla si el apellido es inválido.
    }
    doctor->setApellido(apellido); // Asigna el apellido al objeto `Doctor`.

    // Solicita al usuario que seleccione la especialidad del doctor.
    do {
        cout << "Seleccione especialidad:" << endl;
        cout << "1. Medico General" << endl;
        cout << "2. Oncologia" << endl;
        cout << "3. Fisioterapia" << endl;
        cout << "4. Fauna Silvestre" << endl;
        cin >> opcion; // Lee la opción de especialidad seleccionada por el usuario.
        system("cls"); // Limpia la pantalla después de ingresar la opción.

        // Verifica que la opción seleccionada sea válida (1 a 4).
        while (cin.fail() || opcion < 1 || opcion > 4) {
            cin.clear(); // Limpia el estado de error del flujo de entrada.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora los caracteres inválidos en el buffer de entrada.
            cout << "Opcion invalida. Por favor, seleccione nuevamente:" << endl;
            cout << "1. Medico General" << endl;
            cout << "2. Oncologia" << endl;
            cout << "3. Fisioterapia" << endl;
            cout << "4. Fauna Silvestre" << endl;
            cin >> opcion; // Solicita al usuario que ingrese una opción válida.
            system("cls"); // Limpia la pantalla si la opción es inválida.
        }

        // Asigna la especialidad al objeto `Doctor` basado en la opción seleccionada.
        switch (opcion) {
            case 1:
                especialidad = "Medico General";
                break;
            case 2:
                especialidad = "Oncologia";
                break;
            case 3:
                especialidad = "Fisioterapia";
                break;
            case 4:
                especialidad = "Fauna Silvestre";
                break;
        }
    } while (especialidad.empty()); // Repite hasta que se haya seleccionado una especialidad válida.

    doctor->setEspecialidad(especialidad); // Asigna la especialidad al objeto `Doctor`.

    doctores.push_back(*doctor); // Agrega el objeto `Doctor` a la lista de doctores.

    // Abre el archivo DOCTORES.TXT en modo de añadir (append) para agregar los datos del nuevo doctor.
    ofstream archivo("DOCTORES.TXT", ios::app);
    if (archivo.is_open()) { // Verifica si el archivo se ha abierto correctamente.
        archivo << cedula << "," << nombre << "," << apellido << "," << especialidad << endl;
        archivo.close(); // Cierra el archivo después de escribir los datos.
        cout << "Doctor registrado con exito." << endl; // Muestra un mensaje de éxito.
    } else {
        cout << "No se pudo abrir el archivo DOCTORES.TXT para guardar el doctor." << endl; // Muestra un mensaje de error si el archivo no se abre.
    }

    delete doctor; // Libera la memoria asignada al objeto `Doctor`.
}


// Esta función verifica si una cadena de texto contiene al menos un dígito (0-9).
bool contieneDigitos(const string& str) {
    // `any_of` verifica si al menos uno de los caracteres en `str` cumple con la condición especificada.
    // `str.begin()` y `str.end()` definen el rango de caracteres a revisar.
    // `::isdigit` es una función que determina si un carácter es un dígito.
    return any_of(str.begin(), str.end(), ::isdigit);
}

// Esta función verifica si una cadena de texto contiene al menos un carácter especial.
// Los caracteres especiales son aquellos que no son letras, dígitos, ni espacios.
bool contieneCaracteresEspeciales(const string& str) {
    // Itera sobre cada carácter en la cadena `str`.
    for (char c : str) {
        // Verifica si el carácter no es alfanumérico y no es un espacio.
        // `isalnum(c)` determina si `c` es una letra o un dígito.
        // `c != ' '` verifica que `c` no es un espacio.
        if (!isalnum(c) && c != ' ') {
            // Si encuentra un carácter especial, retorna `true`.
            return true;
        }
    }
    // Si no encuentra caracteres especiales, retorna `false`.
    return false;
}


void registrarCita() {
    system("cls");  // Limpia la pantalla al inicio de la función

    while (true) {
        try {
            system("cls");
            // Solicitar el código de la cita al usuario
            string codigoStr;
            int codigo;
            cout << "Ingrese el codigo de la cita (a partir de 1000): ";
            cin >> codigoStr;
            system("cls");  // Limpia la pantalla

            // Validar el código de la cita
            if (!soloDigitos(codigoStr)) {
                mostrarError("El codigo debe ser numerico.");
                continue;
            }

            codigo = stoi(codigoStr);
            if (codigo < 1000) {
                mostrarError("El codigo debe ser a partir de 1000.");
                continue;
            }

            // Verificar si el código de cita ya existe
            bool codigoExiste = false;
            for (Cita& cita : citas) {
                if (cita.getCodigo() == codigo) {
                    mostrarError("El codigo de cita ya existe. Ingrese otro codigo.");
                    codigoExiste = true;
                    break;
                }
            }
            if (codigoExiste) continue;

            // Solicitar la cédula del cliente
            system("cls");
            string cedulaClienteStr;
            int cedulaCliente;
            cout << "Ingrese el numero de cedula del duenio de la mascota: ";
            cin >> cedulaClienteStr;
            system("cls");  // Limpia la pantalla

            // Validar la cédula del cliente
            if (!soloDigitos(cedulaClienteStr)) {
                mostrarError("La cedula debe ser numerica.");
                continue;
            }

            cedulaCliente = stoi(cedulaClienteStr);
            Cliente cliente;

            // Buscar al cliente por número de cédula
            bool clienteEncontrado = false;
            for (Cliente c : clientes) {
                if (c.getNumeroCedula() == cedulaCliente) {
                    cliente = c;
                    clienteEncontrado = true;
                    break;
                }
            }

            if (!clienteEncontrado) {
                mostrarError("Cliente no encontrado. La cita no se puede registrar.");
                continue;
            }

            // Solicitar la cédula del doctor
            string cedulaDoctorStr;
            int cedulaDoctor;
            system("cls");
            cout << "Ingrese el numero de cedula del doctor: ";
            cin >> cedulaDoctorStr;
            system("cls");  // Limpia la pantalla

            // Validar la cédula del doctor
            if (!soloDigitos(cedulaDoctorStr)) {
                mostrarError("La cedula debe ser numerica.");
                continue;
            }

            cedulaDoctor = stoi(cedulaDoctorStr);
            Doctor doctor;

            // Buscar al doctor por número de cédula
            bool doctorEncontrado = false;
            for (Doctor d : doctores) {
                if (d.getNumeroCedula() == cedulaDoctor) {
                    doctor = d;
                    doctorEncontrado = true;
                    break;
                }
            }

            if (!doctorEncontrado) {
                mostrarError("Doctor no encontrado. La cita no se puede registrar.");
                continue;
            }

            // Solicitar el día de la cita
            int diaNumero;
            string dia;
            while (true) {
                system("cls");
                cout << "Ingrese el dia de la semana para la cita (1-Lunes, 2-Martes, 3-Miercoles, 4-Jueves, 5-Viernes, 6-Sabado, 7-Domingo): ";
                cin >> diaNumero;
                system("cls");  // Limpia la pantalla

                if (cin.fail() || diaNumero < 1 || diaNumero > 7) {
                    cin.clear();  // Limpia el estado de error de cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia el buffer de entrada
                    mostrarError("Dia invalido. Ingrese un numero entre 1 y 7.");
                } else {
                    switch (diaNumero) {
                        case 1: dia = "Lunes"; break;
                        case 2: dia = "Martes"; break;
                        case 3: dia = "Miercoles"; break;
                        case 4: dia = "Jueves"; break;
                        case 5: dia = "Viernes"; break;
                        case 6: dia = "Sabado"; break;
                        case 7: dia = "Domingo"; break;
                    }
                    break;  // Salir del bucle si la entrada es válida
                }
            }

            // Solicitar la hora de la cita
            int horas, minutos;
            while (true) {
                system("cls");
                cout << "Ingrese las horas de la cita (en formato 24 horas, de 7 a 19): ";
                cin >> horas;
                system("cls");  // Limpia la pantalla

                if (cin.fail() || horas < 7 || horas > 19) {
                    cin.clear();  // Limpia el estado de error de cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia el buffer de entrada
                    mostrarError("Hora invalida. Ingrese las horas de la cita (de 7 a 19 en formato 24 horas).");
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            }

            while (true) {
                system("cls");
                cout << "Ingrese los minutos de la cita: ";
                cin >> minutos;
                system("cls");  // Limpia la pantalla

                if (cin.fail() || minutos < 0 || minutos > 59) {
                    cin.clear();  // Limpia el estado de error de cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia el buffer de entrada
                    mostrarError("Minutos invalidos. Ingrese los minutos de la cita (0-59).");
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            }

            Hora hora;
            hora.setHora(horas);
            hora.setMinuto(minutos);

            // Solicitar la observación de la cita
            cin.ignore();  // Limpiar buffer de entrada
            string observacion;
            while (true) {
                system("cls");
                cout << "Ingrese una breve observacion de la razon de la consulta: ";
                getline(cin, observacion);
                system("cls");  // Limpia la pantalla

                if (contieneCaracteresEspeciales(observacion) || contieneDigitos(observacion)) {
                    mostrarError("La observacion no puede contener caracteres especiales (excepto espacio) ni solo numeros.");
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            }

            // Crear la nueva cita y asignar los datos
            Cita nuevaCita;
            nuevaCita.setCodigo(codigo);
            nuevaCita.setCliente(cliente);
            nuevaCita.setDoctor(doctor);
            nuevaCita.setDia(dia);  // Se asigna el nuevo atributo 'dia'
            nuevaCita.setHora(hora);
            nuevaCita.setObservacion(observacion);

            // Agregar la nueva cita a la lista de citas
            citas.push_back(nuevaCita);

            // Guardar la cita en el archivo CITAS.TXT
            ofstream archivo("CITAS.TXT", ios::app);
            if (archivo.is_open()) {
                archivo << nuevaCita.getCodigo() << "|"
                        << nuevaCita.getCliente().getNumeroCedula() << "|"
                        << nuevaCita.getDoctor().getNumeroCedula() << "|"
                        << nuevaCita.getDia() << "|"
                        << nuevaCita.getHora().getHora() << ":"
                        << nuevaCita.getHora().getMinuto() << "|"
                        << nuevaCita.getObservacion() << endl;
                archivo.close();
                cout << "Cita registrada con exito." << endl;
            } else {
                mostrarError("No se pudo abrir el archivo CITAS.TXT para guardar la cita.");
            }
            break; // Salir del bucle principal si todo es correcto
        } catch (const std::out_of_range& e) {
            mostrarError("El numero ingresado esta fuera del rango permitido.");
        } catch (const std::invalid_argument& e) {
            mostrarError("El valor ingresado no es válido.");
        }
    }
}



bool validarCodigoCita(int codigo) {  // Define una función que verifica si un código de cita es válido.
    return codigo >= 1000;            // Retorna true si el código es mayor o igual a 1000, false en caso contrario.
}                                    // La función usa un operador de comparación para validar el código de cita.


// Función para validar opción S/N
bool validarOpcionSN(string opcion) {  // Define una función que valida si una opción es 'S', 's', 'N' o 'n'.
    return opcion == "S" || opcion == "s" || opcion == "N" || opcion == "n";  // Retorna true si la opción es una de las válidas, false en caso contrario.
}  // Fin de la función que comprueba si la opción es válida según los criterios especificados.
bool validarOpcionS(string opcion) {  // Define una función para validar si la opción es 'S' o 's'.
    return opcion == "S" || opcion == "s";  // Devuelve true si 'opcion' es igual a "S" o "s", y false en caso contrario.
}  // Fin de la función que verifica si la opción es 'S' o 's'.
bool validarOpcionN(string opcion) {  // Define una función para validar si la opción es 'N' o 'n'.
    return opcion == "N" || opcion == "n";  // Devuelve true si 'opcion' es igual a "N" o "n", y false en caso contrario.
}  // Fin de la función que verifica si la opción es 'N' o 'n'.


void reportarCitasPorDoctor() {
    system("cls");  // Limpia la pantalla al inicio de la función

    string cedulaOpcional;  // Variable para almacenar la cédula del doctor como cadena
    int cedula;  // Variable para almacenar la cédula del doctor como entero
    bool doctorEncontrado = false;  // Bandera para verificar si el doctor existe en la lista

    // Solicita al usuario que ingrese la cédula del doctor
    cout << "Ingrese numero de cedula del doctor: ";
    cin >> cedulaOpcional;

    // Verifica que la cédula ingresada sea válida
    while (!validarCedula(cedulaOpcional)) {
        system("cls");
        cout << "Cedula invalida. Ingrese nuevamente (exactamente 9 digitos): ";
        cin >> cedulaOpcional;
    }
    cedula = stoi(cedulaOpcional);  // Convierte la cédula de cadena a entero

    Doctor doctor;

    // Busca al doctor en la lista de doctores
    for (Doctor& d : doctores) {
        if (d.getNumeroCedula() == cedula) {
            doctor = d;  // Asigna el doctor encontrado a la variable local
            doctorEncontrado = true;  // Marca que se encontró al doctor
            break;  // Sale del ciclo una vez que se encuentra al doctor
        }
    }

    // Si el doctor no se encuentra, muestra un mensaje de error y regresa al menú
    if (!doctorEncontrado) {
        system("cls");
        cout << "Doctor no encontrado." << endl;
        system("pause");  // Pausa el programa para que el usuario vea el mensaje
        return;  // Sale de la función si el doctor no está registrado
    }

    bool citasEncontradas = false;  // Bandera para verificar si hay citas asociadas al doctor

    system("cls");
    cout << "El Doctor: " << doctor.getNombre() << " " << doctor.getApellido() << endl << endl;

    // Muestra las citas del doctor
    for (Cita& cita : citas) {
        if (cita.getDoctor().getNumeroCedula() == cedula) {
            if (!citasEncontradas) {
                cout << "Numero Cita\tDia\tHora\tNombre Mascota\tTipo de Mascota\tObservacion" << endl;
                citasEncontradas = true;  // Marca que se han encontrado citas
            }
            // Muestra los detalles de cada cita
            cout << cita.getCodigo() << "\t\t"
                 << cita.getDia() << "\t"  // Obtiene el día de la cita
                 << cita.getHora().getHora() << ":" << cita.getHora().getMinuto() << "\t"  // Muestra la hora de la cita
                 << cita.getCliente().getMascota().getNombre() << "\t\t"  // Muestra el nombre de la mascota
                 << cita.getCliente().getMascota().getTipo() << "\t\t"  // Muestra el tipo de la mascota
                 << cita.getObservacion() << endl;  // Muestra la observación de la cita
        }
    }

    // Muestra un mensaje si no hay citas para el doctor
    if (!citasEncontradas) {
        cout << "No hay citas para este doctor." << endl;
    }

    string opcion;
    // Solicita al usuario si desea volver al menú principal o salir del programa
    cout << "Desea volver al menu principal? S/N: ";
    cin >> opcion;
    while (opcion != "S" && opcion != "N" && opcion != "s" && opcion != "n") {
        system("cls");
        cout << "Opcion invalida. Desea volver al menu principal? S/N: ";
        cin >> opcion;
    }

    if (opcion == "N" || opcion == "n") {
        while (true) {
            system("cls");
            cout << "Quieres salir del programa? S/N: ";
            cin >> opcion;
            if (opcion == "S" || opcion == "s") {
                exit(0);  // Sale del programa con código 0 (éxito)
            } else if (opcion == "N" || opcion == "n") {
                break;  // Sale del ciclo y regresa al menú principal
            } else {
                system("cls");
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
    }
}
void reportarCitasPorCliente() {
    system("cls");  // Limpia la pantalla al inicio de la función

    string cedulaOpcional;  // Variable para almacenar la cédula del cliente como cadena
    int cedula;  // Variable para almacenar la cédula del cliente como entero
    bool clienteEncontrado = false;  // Bandera para verificar si el cliente existe en la lista

    // Solicita al usuario que ingrese la cédula del cliente
    cout << "Ingrese numero de cedula del cliente: ";
    cin >> cedulaOpcional;

    // Verifica que la cédula ingresada sea válida
    while (!validarCedula(cedulaOpcional)) {
        system("cls");
        cout << "Cedula invalida. Ingrese nuevamente (exactamente 9 digitos): ";
        cin >> cedulaOpcional;
    }
    cedula = stoi(cedulaOpcional);  // Convierte la cédula de cadena a entero

    Cliente cliente;

    // Busca al cliente en la lista de clientes
    for (Cliente& c : clientes) {
        if (c.getNumeroCedula() == cedula) {
            cliente = c;  // Asigna el cliente encontrado a la variable local
            clienteEncontrado = true;  // Marca que se encontró al cliente
            break;  // Sale del ciclo una vez que se encuentra al cliente
        }
    }

    // Si el cliente no se encuentra, muestra un mensaje de error y regresa al menú
    if (!clienteEncontrado) {
        system("cls");
        cout << "Cliente no encontrado." << endl;
        system("pause");  // Pausa el programa para que el usuario vea el mensaje
        return;  // Sale de la función si el cliente no está registrado
    }

    bool citasEncontradas = false;  // Bandera para verificar si hay citas asociadas al cliente

    system("cls");
    cout << "El Cliente: " << cliente.getNombre() << " " << cliente.getApellido() << endl << endl;

    // Muestra las citas del cliente
    for (Cita& cita : citas) {
        if (cita.getCliente().getNumeroCedula() == cedula) {
            if (!citasEncontradas) {
                cout << "Numero Cita\tDia\tHora\tNombre Mascota\tObservacion" << endl;
                citasEncontradas = true;  // Marca que se han encontrado citas
            }
            // Muestra los detalles de cada cita
            cout << cita.getCodigo() << "\t\t"
                 << cita.getDia() << "\t"  // Obtiene el día de la cita
                 << cita.getHora().getHora() << ":" << cita.getHora().getMinuto() << "\t"  // Muestra la hora de la cita
                 << cita.getCliente().getMascota().getNombre() << "\t\t"  // Muestra el nombre de la mascota
                 << cita.getObservacion() << endl;  // Muestra la observación de la cita
        }
    }

    // Muestra un mensaje si no hay citas para el cliente
    if (!citasEncontradas) {
        cout << "No hay citas para este cliente." << endl;
    }

    string opcion;
    // Solicita al usuario si desea volver al menú principal o salir del programa
    cout << "Desea volver al menu principal? S/N: ";
    cin >> opcion;
    while (opcion != "S" && opcion != "N" && opcion != "s" && opcion != "n") {
        system("cls");
        cout << "Opcion invalida. Desea volver al menu principal? S/N: ";
        cin >> opcion;
    }

    if (opcion == "N" || opcion == "n") {
        while (true) {
            system("cls");
            cout << "Quieres salir del programa? S/N: ";
            cin >> opcion;
            if (opcion == "S" || opcion == "s") {
                exit(0);  // Sale del programa con código 0 (éxito)
            } else if (opcion == "N" || opcion == "n") {
                break;  // Sale del ciclo y regresa al menú principal
            } else {
                system("cls");
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
    }
}


void mostrarMenu()  // Define una función que muestra el menú de opciones al usuario.
{
    system("cls");  // Limpia la pantalla para que el menú sea visible desde una pantalla limpia.

    // Muestra el encabezado del menú.
    cout << "Menu de opciones:" << endl;

    // Muestra la opción 1 del menú.
    cout << "1. Ingresar datos del doctor." << endl;
    // Muestra la opción 2 del menú.
    cout << "2. Ingresar datos del cliente." << endl;
    // Muestra la opción 3 del menú.
    cout << "3. Registrar una cita." << endl;
    // Muestra la opción 4 del menú.
    cout << "4. Reporte de citas por doctor." << endl;
    // Muestra la opción 5 del menú.
    cout << "5. Reporte de citas por cliente." << endl;
    // Muestra la opción 6 del menú.
    cout << "6. Salir." << endl;
}

void menu() {
    int opcion;  // Variable para almacenar la opción seleccionada por el usuario.
    do {  // Bucle principal del menú que se ejecuta hasta que el usuario elige la opción de salir (opción 6).
        try {
            system("cls");  // Limpia la pantalla.
            mostrarMenu();  // Llama a la función que muestra el menú de opciones al usuario.

            // Validar la entrada del usuario
            while (!(cin >> opcion)) {  // Verifica si la entrada del usuario es válida (un número entero).
                cin.clear();  // Limpia el estado de error de cin para permitir nuevas entradas.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora el resto de la entrada inválida.
                system("cls");  // Limpia la pantalla.
                mostrarMenu();  // Muestra el menú de opciones nuevamente.
                cout << "Entrada invalida. Por favor, ingrese un numero entero. Seleccione una opcion: ";  // Solicita una entrada válida.
            }

            switch (opcion) {  // Evalúa la opción seleccionada por el usuario.
                case 1:  // Si la opción es 1, llama a la función para ingresar datos del doctor.
                    ingresarDoctor();
                    break;
                case 2:  // Si la opción es 2, llama a la función para ingresar datos del cliente.
                    ingresarCliente();
                    break;
                case 3:  // Si la opción es 3, llama a la función para registrar una cita si hay clientes y doctores.
                    if (!clientes.empty() && !doctores.empty()) {  // Verifica que haya al menos un cliente y un doctor para registrar una cita.
                        registrarCita();
                    } else {  // Si no hay información suficiente, muestra un mensaje al usuario.
                        cout << "No hay informacion suficiente almacenada para completar una cita." << endl;
                    }
                    break;
                case 4:  // Si la opción es 4, llama a la función para generar un reporte de citas por doctor si hay doctores.
                    if (!doctores.empty()) {  // Verifica que haya al menos un doctor para reportar citas.
                        reportarCitasPorDoctor();
                    } else {  // Si no hay doctores, muestra un mensaje al usuario.
                        cout << "No hay doctores creados aun." << endl;
                    }
                    break;
                case 5:  // Si la opción es 5, llama a la función para generar un reporte de citas por cliente si hay clientes.
                    if (!clientes.empty()) {  // Verifica que haya al menos un cliente para reportar citas.
                        reportarCitasPorCliente();
                    } else {  // Si no hay clientes, muestra un mensaje al usuario.
                        cout << "No hay clientes creados aun." << endl;
                    }
                    break;
                case 6:  // Si la opción es 6, muestra un mensaje de despedida y sale del bucle.
                    cout << "Saliendo del programa." << endl;
                    break;
                default:  // Si la opción no es válida (no está entre 1 y 6), muestra un mensaje de error.
                    cout << "Opcion invalida. Por favor, seleccione nuevamente." << endl;
                    break;
            }

            system("pause");  // Pausa la ejecución para que el usuario pueda leer el mensaje antes de volver al menú.

        } catch (const std::out_of_range& e) {
            mostrarError("El número ingresado está fuera del rango permitido.");
        } catch (const std::invalid_argument& e) {
            mostrarError("El valor ingresado no es válido.");
        } catch (const std::exception& e) {
            mostrarError(string("Ocurrió un error inesperado: ") + e.what());
        }

    } while (opcion != 6);  // Repite el bucle hasta que el usuario seleccione la opción 6 para salir del programa.
}

int main()  // Punto de entrada del programa.
{
    leerDoctores();  // Llama a la función para leer los datos de los doctores desde un archivo o una fuente de datos.
    leerClientes();  // Llama a la función para leer los datos de los clientes desde un archivo o una fuente de datos.
    leerCitas();  // Llama a la función para leer los datos de las citas desde un archivo o una fuente de datos.

    menu();  // Llama a la función que muestra el menú de opciones al usuario y gestiona la selección de opciones.

    return 0;  // Finaliza el programa y retorna 0 al sistema operativo, indicando que la ejecución fue exitosa.
}
