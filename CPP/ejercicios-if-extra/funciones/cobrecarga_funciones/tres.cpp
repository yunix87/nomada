#include <iostream>
using namespace std;

int main() {

    int numero[5]={10,20,30,40,50};
    int suma =0;

    for( int i=0; i<5; i++){
        suma+= numero[i];
    }
cout<<"La suma es: "<<suma<<endl;
    return 0;
}