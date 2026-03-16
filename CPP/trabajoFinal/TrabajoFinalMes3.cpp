#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;


enum EstadoAcademico { DESAPROBADO = 0, APROBADO = 1 };


struct Estudiante {
    int codigo;
    char nombre[60];
    int edad;
    float promedio;
    EstadoAcademico estado;
};


void agregarEstudiante(Estudiante*& lista, int& n);
void mostrarEstudiantes(const Estudiante* lista, int n);
void guardarArchivo(const Estudiante* lista, int n);
void cargarArchivo(Estudiante*& lista, int& n);
void liberarMemoria(Estudiante*& lista);

int main() {
    Estudiante *estudiantes = nullptr; 
    int cantidad = 0;
    int opcion;

    do {
        cout << "\n====================================" << endl;
        cout << "   SISTEMA DE GESTION ACADEMICA" << endl;
        cout << "====================================" << endl;
        cout << "1. Agregar estudiante" << endl;
        cout << "2. Mostrar todos los estudiantes" << endl;
        cout << "3. Guardar estudiantes en archivo" << endl;
        cout << "4. Cargar estudiantes desde archivo" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        
        if (!(cin >> opcion)) { 
            cout << "Por favor, ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (opcion) {
            case 1: agregarEstudiante(estudiantes, cantidad); break;
            case 2: mostrarEstudiantes(estudiantes, cantidad); break;
            case 3: guardarArchivo(estudiantes, cantidad); break;
            case 4: cargarArchivo(estudiantes, cantidad); break;
            case 5: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 5);

    liberarMemoria(estudiantes);
    return 0;
}



void agregarEstudiante(Estudiante*& lista, int& n) {
    
    Estudiante* nuevaLista = new Estudiante[n + 1];
       
    for (int i = 0; i < n; i++) {
        nuevaLista[i] = lista[i];
    }

    
    cout << "\nCodigo: "; cin >> nuevaLista[n].codigo;
    cin.ignore(); 
    cout << "Nombre: "; cin.getline(nuevaLista[n].nombre, 50);
    cout << "Edad: "; cin >> nuevaLista[n].edad;
    cout << "Promedio: "; cin >> nuevaLista[n].promedio;

    nuevaLista[n].estado = (nuevaLista[n].promedio >= 10.5) ? APROBADO : DESAPROBADO;

        delete[] lista; 
    lista = nuevaLista; 
    n++;
    cout << "Registro exitoso." << endl;
}


void mostrarEstudiantes(const Estudiante* lista, int n) {
    if (n == 0) {
        cout << "\nNo hay datos registrados." << endl;
        return;
    }

   
    cout << "\n" << setw(65) << setfill('-') << "" << endl;
    cout << setfill(' ') << left << setw(10) << "CODIGO" << setw(25) << "NOMBRE" 
         << setw(8) << "EDAD" << setw(12) << "PROMEDIO" << "ESTADO" << endl;
    cout << setw(65) << setfill('-') << "" << setfill(' ') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << lista[i].codigo 
             << setw(25) << lista[i].nombre 
             << setw(8) << lista[i].edad 
             << setw(12) << fixed << setprecision(2) << lista[i].promedio
             << (lista[i].estado == APROBADO ? "APROBADO" : "DESAPROBADO") << endl;
    }
}

void guardarArchivo(const Estudiante* lista, int n) {
    ofstream archivo("datos_estudiantes.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir archivo." << endl;
        return;
    }
    
    archivo.write(reinterpret_cast<const char*>(&n), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(lista), sizeof(Estudiante) * n);
    archivo.close();
    cout << "Datos guardados." << endl;
}

void cargarArchivo(Estudiante*& lista, int& n) {
    ifstream archivo("datos_estudiantes.dat", ios::binary);
    if (!archivo) {
        cout << "No se encontro archivo previo." << endl;
        return;
    }
    liberarMemoria(lista);
    archivo.read(reinterpret_cast<char*>(&n), sizeof(int));
    lista = new Estudiante[n];
    archivo.read(reinterpret_cast<char*>(lista), sizeof(Estudiante) * n);
    archivo.close();
    cout << "Carga exitosa." << endl;
}

void liberarMemoria(Estudiante*& lista) {
    if (lista != nullptr) {
        delete[] lista;
        lista = nullptr;
    }
}