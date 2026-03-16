//Cre un programa que genre una lista de número aleatorios en un rango definido por el usuario
//y separa los número en pared e impares

#include <iostream>
using namespace std;

int main() {

    srand(time(0));

    int pares = 0;
    int impares = 0;    
    int cantidad, min, max;

    cout << "Ingrese la cantidad de números: ";
    cin >> cantidad;
    cout << "Ingrese el número mínimo: ";
    cin >> min;
    cout << "Ingrese el número máximo: ";
    cin >> max;
    
    int numeros[cantidad];

    cout << "Estos son los números generados: "<<endl;

    for (int i = 0; i < cantidad; i++) {
        numeros[i] = min + rand() % (max -min + 1);
        //cout << numeros[i] << " ";
        //cout << endl;5
        if (numeros[i] % 2 == 0) {
            pares++;
            cout << "Par: " << numeros[i] << endl;

        } else {
            impares++;
            cout << "Impar: " << numeros[i] << endl;
        }
    }
          
    cout << endl;
       
    cout << "Cantidad de números pares: " << pares << endl;
    cout << "Cantidad de números impares: " << impares << endl;

    return 0;
}