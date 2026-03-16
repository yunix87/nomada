#include <iostream>
using namespace std;

int main() {

    int x=0, y=0;
    int aux=0;
    // Solicitar al usuario que ingrese dos enteros
    
    /* Leer los valores ingresados por el usuario */
    cout<< "Ingrese el primer entero: ";
     cin >> x;

    cout<< "Ingrese el segundo entero: ";
    cin >> y;
    aux = x + y;
    cout << "La suma es : " << aux << endl;
    return 0;
}