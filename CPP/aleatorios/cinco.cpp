//Cree un programa que genre una contraseña aleatoria de 10 caracteres que incluya número, letras mayúsculas, minúsculas y
//dígitos. de una longitud especificada.
//ingresada

 
#include <iostream>
using namespace std;

int main() {

    int longitud;
    cout << "Ingrese la longitud de la contraseña: ";
    cin >> longitud;
    
    // Generar contraseña aleatoria
    string contraseña = "";
    string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    
    for (int i = 0; i < longitud; i++) {
        int index = rand() % caracteres.length();
        contraseña += caracteres[index];
    }
    
    cout << "Contraseña generada: " << contraseña << endl;

    

    return 0;
}