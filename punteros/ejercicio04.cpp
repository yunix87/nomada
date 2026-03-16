//escribe un programa que invierta los elementos de un arreglo 
// utilizando una función que manipule punteros.

#include <iostream>
using namespace std;

void invertir(int *arreglo, int n) {
    int *inicio = arreglo;
    int *fin = arreglo + n - 1;
    while (inicio < fin) {
        int temp = *inicio;
        *inicio = *fin;
        *fin = temp;
        inicio++;
        fin--;
    }
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
    invertir(arreglo, n);
    cout << "El arreglo invertido es: ";
    for (int i = 0; i < n; i++) {
        cout << *(arreglo + i) << " ";
    }
    delete []arreglo;
    return 0;
}
