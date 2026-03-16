#include <iostream>     // Librería estándar para entrada/salida en consola
#include <fstream>      // Librería para manejo de archivos
#include <string>       // Librería para usar cadenas de texto (std::string)
using namespace std;    // Para evitar escribir std:: en cada instrucción

// Definimos una estructura para representar una persona
struct Persona {
    char nombre[50];    // Campo de texto fijo de 50 caracteres
    int edad;           // Campo numérico para la edad
};

int main() {
    // 1. Crear un objeto de tipo Persona y asignar valores
    Persona p1;
    cout << "Ingrese nombre: ";
    cin.getline(p1.nombre, 50);   // Leer nombre desde teclado
    cout << "Ingrese edad: ";
    cin >> p1.edad;               // Leer edad desde teclado

    // 2. Abrir un archivo binario para escritura
    ofstream archivo("personas.dat", ios::out | ios::binary);
    archivo.write(reinterpret_cast<char*>(&p1), sizeof(Persona));
    archivo.close();   // Cerrar archivo para asegurar que se guarde

    // 3. Abrir el archivo binario para lectura
    ifstream archivoLectura("personas.dat", ios::in | ios::binary);
    Persona p2;
    archivoLectura.read(reinterpret_cast<char*>(&p2), sizeof(Persona));
    archivoLectura.close();

    // 4. Mostrar los datos recuperados
    cout << "\nDatos leídos desde el archivo:" << endl;
    cout << "Nombre: " << p2.nombre << endl;
    cout << "Edad: " << p2.edad << endl;

    return 0;
}
