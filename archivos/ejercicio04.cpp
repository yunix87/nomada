//escribe un programa que lea un archivo de tecto y cuente el número de lineas y palabras
//stringstream

# include <iostream>
# include <fstream>

using namespace std;

void contarLineasPalabras(){
string nombreArchivo, linea;

int lineas = 0;
int palabras = 0;

cout << "Ingrese el nombre del archivo: ";
cin >> nombreArchivo;


ifstream archivo(nombreArchivo);
if (!archivo) {
    string linea;
    while (getline(archivo, linea)) {
        lineas++;
        stringstream ss(linea);
        string palabra;
        while (ss >> palabra) {
            palabras++;
        }
    }
    cout << "El archivo tiene " << lineas << " lineas y " << palabras << " palabras." << endl;
    archivo.close();
} else {
    cout << "Error al abrir el archivo." << endl;
}

int main() {
    contarLineasPalabras();
    return 0;
}


}