//Escribe un programa que determine su una palabra es palindromo
//utilizando punteros para realizar la comparacion

#include <iostream>
using namespace std;

int longitudCadena(char *texto) {
    int contador = 0;
    while (*texto != '\0') {
        contador++;
        texto++;
    }
    return contador;
}
bool palindromo(char *palabra) {
    int n = longitudCadena(palabra);
    char *inicio = palabra;
    char *fin = palabra + n - 1;
    while (inicio < fin) {
        if (*inicio != *fin) {
            return false;
        }
        inicio++;
        fin--;
    }
    return true;
}


int main() {
    char palabra[100];
    cout << "Ingrese una palabra: ";
    cin >> palabra;

    if (palindromo(palabra)) {
        cout << "La palabra es palindromo" << endl;
    } else {
        cout << "La palabra no es palindromo" << endl;
    }
    return 0;
}
