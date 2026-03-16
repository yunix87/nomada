//Escribe  un programa que encuentre el valor máximo de un arreglo de
//enteros usando una función 
//que manipule punteros.

#include <iostream>
using namespace std;

int maximo(int *arreglo, int n) {
    int max = *arreglo;
    for (int i = 1; i < n; i++) {
        if (*(arreglo + i) > max) {
            max = *(arreglo + i);
        }
    }
    return max;
}

int main() {
    int n;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;
    int *arreglo = new int[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Ingrese el elemento " << i << ": ";
        cin >> *(arreglo + i);
    }
    cout << "El valor maximo del arreglo es: " << maximo(arreglo, n) << endl;
    delete []arreglo;
    return 0;
}
