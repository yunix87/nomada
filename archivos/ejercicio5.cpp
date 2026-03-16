//Escriba un programa que lea número enteros de un archivo y genere
//otro archivo que contenga solo número positivos

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    ofstream archivoSalida("positivos.txt");
    if (!archivoSalida) {
        cout << "Error al crear el archivo de salida." << endl;
        return 1;
    }
    int numero;
    while (archivo >> numero) {
        if (numero > 0) {
            archivoSalida << numero << endl;
        }
    }
    archivo.close();
    archivoSalida.close();
    cout << "Se han guardado los números positivos en el archivo positivos.txt" << endl;
    return 0;
}
