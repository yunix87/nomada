//modifica el elemento de una matriz

#include <iostream>
using namespace std;

int main() {
    const int filas = 3;
    const int columnas = 3; 
    int matriz[filas][columnas];

    // Inicializar la matriz con valores
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = i * columnas + j + 1;
        }
    }

    // Mostrar la matriz original
    cout << "Matriz original:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    // Modificar un elemento específico
    int fila, columna, nuevoValor;
    cout << "Ingrese la fila del elemento a modificar: ";
    cin >> fila;
    cout << "Ingrese la columna del elemento a modificar: ";
    cin >> columna;
    cout << "Ingrese el nuevo valor: ";
    cin >> nuevoValor;

    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        matriz[fila][columna] = nuevoValor;
        cout << "Elemento modificado correctamente." << endl;
    } else {
        cout << "Coordenadas fuera de rango." << endl;
    }

    // Mostrar la matriz modificada
    cout << "Matriz modificada:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}