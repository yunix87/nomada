//usando metodos recursivos, calcular el enesimo número fibonacci, valudar que el numero sea no negativo

#include <iostream>
#include <limits>

using namespace std;

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int leerEnteroNoNegativo() {
    int numero;
    while (true) {
        cout << "Ingrese un numero entero no negativo: ";
        cin >> numero;
        
        if (cin.fail() || numero < 0) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Entrada inválida. Intente nuevamente." << endl;
        } else {
            return numero;
        }
    }
}

int main() {
    int n = leerEnteroNoNegativo(); 
    cout << "El termino Fibonacci en la posicion " << n << " es: " << fibonacci(n) << endl;
    
    for (int i = 0; i <n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    return 0;
}