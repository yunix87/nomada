#include <iostream>
using namespace std;

void invertirArreglo(int arreglo[], int tam){
    int inicio =0;
    int fin = tam -1;
    while(inicio<fin){
        int temp = arreglo[inicio];
        arreglo[inicio]= arreglo[fin];
        arreglo[fin]= temp;
        inicio++;
        fin--;
    }

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

    invertirArreglo(arreglo, tam);
    cout<<"El arreglo invertido es: ";
    for(int i=0;i<tam;i++){
        cout<<arreglo[i]<<" ";
    }   
    return 0;
}