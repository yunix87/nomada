// Crea un programa que permita realizar operaciones básicas(suma, resta)
//multiplicación y división
//entre dos números utilizando punteros para devolver los resultados

#include <iostream>
using namespace std;

void operaciones(float pto_a, float pto_b, float *pto_suma, float *pto_resta, float *pto_multiplicacion, float *pto_division) {
    *pto_suma = pto_a + pto_b;
    *pto_resta = pto_a - pto_b;
    *pto_multiplicacion = pto_a * pto_b;
    *pto_division = (b!=0) ? pto_a / pto_b : 0;// validación de división por cero
}

int main() {
    float a, b, suma, resta, multiplicacion, division;
    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;
    operaciones(&a, &b, &suma, &resta, &multiplicacion, &division);// paso por referencia
    cout << "La suma es: " << suma << endl;
    cout << "La resta es: " << resta << endl;
    cout << "La multiplicacion es: " << multiplicacion << endl;
    cout << "La division es: " << division << endl;
    return 0;
}