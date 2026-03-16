
// usando metodos recursivos, obtener la suma de los primeros n numeros


#include <iostream>

using namespace std;

int sumaRecursiva(int n){
    if(n==1)
    return 1;

    return n+sumaRecursiva(n-1);//3+ 2 + 1
}
int main(){

    int n;
    cout << "Ingrese la cantidad de numeros a sumar: ";
    
    cin >> n;
    // la suma recusiva es:

    cout << "La suma de los primeros " << n << " numeros es: " <<sumaRecursiva(n);
    return 0;
}