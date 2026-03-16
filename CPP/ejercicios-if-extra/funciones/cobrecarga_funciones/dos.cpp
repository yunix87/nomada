//define una funcion potencia que calule el resultado de un npúmero elevado a otro.
//Crear sobrecargas para enteros (int) y decimales (duoble)

#include <iostream>
using namespace std;

double potencia(int base, int exponente) {
    int resultadoInt= 1;
    for (int i = 0; i < exponente; i++) {
        resultadoInt *= base;
    }
    return resultadoInt;
}

double potencia(double base, int exponente) {
    double resultadoDec = 1.0;
    for (int i = 0; i < exponente; i++) {
        resultadoDec *= base;
    }
    return resultadoDec;
}
int main() {

    int baseInt;
    int exponente;
    double baseDouble;
   // double potencia(int baseInt, int exponente);
   // double potencia(double baseDouble, int exponente);
    //double exponenteDouble;

    cout<<"Ingrese base entero: "<<endl; 
        cin>>baseInt;
    cout<<"Ingrese base decimal: "<<endl;
        cin>>baseDouble;
    cout<<"Ingrese exponente entero: "<<endl;
        cin>>exponente;

    cout << "Potencia de entero: " << potencia(baseInt, exponente) << endl;
    cout << "Potencia de decimal: " << potencia(baseDouble, exponente) << endl;

    return 0;
}

