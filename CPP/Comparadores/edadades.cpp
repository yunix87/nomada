/*∗ Escribe un programa que solicite dos edades y muestre si tienen la misma
edad o cuál es mayor. ∗ Solicita un valor booleano y muestra el valor contrario.
∗ Solicita dos números enteros, si ambos números son positivos muestra: “Ambos
son positivos”. Si al menos uno es negativo muestra: “Al menos uno es negativo”.
∗ Declara una variable x con un valor ingresado por teclado. Luego, aumenta su
valor en 5 usando el operador de asignación y muéstralo.*/

#include <iostream>
using namespace std;

int main() {

  int edad1 = 0, edad2 = 0;
  int aux = 0;
  // Solicitar al usuario que ingrese dos edades

  /* Leer los valores ingresados por el usuario */
  cout << "Ingrese la edad de la primera persona" << endl;
  cin >> edad1;
  cout << "Ingresa la edad de la segunda persona" << endl;
  cin >> edad2;
  if (edad1 == edad2) {
    cout << "Las edades son iguales" << endl;
  } else if (edad1 > edad2) {
    aux = edad1 - edad2;
    cout << "La primera persona es mayor por " << aux << " años" << endl;
  } else {
    aux = edad2 - edad1;
    cout << "La segunda persona es mayor por " << aux << " años" << endl;
  }

  return 0;
}