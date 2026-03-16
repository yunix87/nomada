//Lee un número en base 10 y muestre su equivalente en base 2 por metodos recursivos

#include <iostream>
using namespace std;

void binario(int n) {
    if (n == 0) return;
    binario(n / 2);
    cout << n % 2;
}

int main() {
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;
    if (n < 0) {
        cout << "El numero debe ser positivo" << endl;
        return 1;
    }
    if (n == 0) {
        cout << "Binario: 0";
    } else {
       cout << "Binario: ";
       binario(n);
    }
    cout << endl;
    return 0;
}
