//ESCRIBE UN PROGRAMA QUE PERMITA AL USUARIO INGRESAR UN ARREGLO
//LUEGO, BUSCA UN NÚMER DADO Y MUESTRA LA POSICION DE SU PRIMERA Y 
//ULTIMA APARICON EN EL ARREGLO USANDO UNA FUNCION DE BUSQUEDA SECUENCIAL

#include <iostream>
using namespace std;


void buscarNumero(int arr[], int n, int num) {
    int primeraPosicion = -1;
    int ultimaPosicion = -1;    
    for (int i = 0; i < n; i++) {
        if (arr[i] == num) {
            if (primeraPosicion == -1) {
                primeraPosicion = i; 
            }
            ultimaPosicion = i; 
        }
    }
    if (primeraPosicion != -1) {
        cout << "Número encontrado en la posición: " << primeraPosicion << endl;
        cout << "Número encontrado en la posición: " << ultimaPosicion << endl;
    } else {
        cout << "Número no encontrado en el arreglo." << endl;
    }

    
}   

int main() {
    int n, num;
    cout << "Ingrese el tamaño del arreglo: ";  
    cin >> n;
    int arr[n];
    cout << "Ingrese los elementos del arreglo: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }           
    cout << "Ingrese el número a buscar: ";
    cin >> num;      
    buscarNumero(arr, n, num);  
    
       
    return 0;   

}

