#include <iostream>
#include <cmath> // Para la función pow()

using namespace std;

int main() {
    int opcion;
    double num1, num2;

    do {
        cout << "\n--- MENU DE OPERACIONES ---\n";
        cout << "1. Suma\n";
        cout << "2. Resta\n";
        cout << "3. Multiplicación\n";
        cout << "4. División\n";
        cout << "5. Potencia\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion >= 1 && opcion <= 5) {
            cout << "Ingrese el primer número: ";
            cin >> num1;
            cout << "Ingrese el segundo número: ";
            cin >> num2;
        }

        switch (opcion) {
            case 1:
                cout << "Resultado: " << num1 + num2 << endl;
                break;
            case 2:
                cout << "Resultado: " << num1 - num2 << endl;
                break;
            case 3:
                cout << "Resultado: " << num1 * num2 << endl;
                break;
            case 4:
                if (num2 != 0)
                    cout << "Resultado: " << num1 / num2 << endl;
                else
                    cout << "Error: División por cero.\n";
                break;
            case 5:
                cout << "Resultado: " << pow(num1, num2) << endl;
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}
