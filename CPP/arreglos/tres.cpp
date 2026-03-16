#include <iostream>
using namespace std;

int encontrarMayor(int arreglo[], int tam) {
    int mayor = arreglo[0];
    for (int i = 1; i < tam; i++) {
        if (arreglo[i] > mayor) {
            mayor = arreglo[i];
        }
    }
    return mayor;
}
int main() {

    int tam;
    cout<<"Ingresa la cantidad de elementos del arreglo: ";
    cin>>tam;
    int arreglo[tam];

    for(int i=0;i<tam;i++){
        cout<<"Ingresa el elemento: "<<i+1<<": ";
        cin>>arreglo[i];
    }

    cout<<"El mayor elemento del arreglo es: "<<encontrarMayor(arreglo, tam)<<endl;
    return 0;
}