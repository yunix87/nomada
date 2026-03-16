// Crear una función que cuente cuantos números pares hay en un arreglo de enteros.
#include <iostream>
using namespace std;

int contadorPares(int arreglo[], int tam){

    int contador=0;
    for(int i=0;i<tam;i++){
        if(arreglo[i]%2==0){
            contador++;
        }
    }
    return contador;
}
int main() {

    int tam;
    cout<<"** Contador de número pares **"<<endl;
    cout<<"Ingresa la cantidad de elementos del arreglo: ";
    cin>>tam;
    int arreglo[tam];

    for(int i=0;i<tam;i++){
        cout<<"Ingresa el elemento: "<<i+1<<": ";
        cin>>arreglo[i];
    }
    cout<<"Los numeros pares en el arreglo son: "<<contadorPares(arreglo, tam)<<endl;
    return 0;
}