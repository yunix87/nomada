#include<iostream>
using namespace std;
int main(){
    int dia,mes;
    cout<<"Ingrese el mes válido: ";
    cin>>mes;
    cout<<"Ingrese el día válido: ";
    cin>>dia;
    if(dia<1 || dia>31 || mes<1 || mes>12){
        cout<<"Fecha inválida"<<endl;
        return 1;
    }

    
    switch(mes) {
case 1:
case 2: cout<<"verano"<<endl; break;
case 3:if(dia<21) cout<<"verano"<<endl;
        else cout<<"otoño"<<endl; break;
case 4:
case 5: cout<<"otoño"<<endl; break; 
case 6: if(dia<21) cout<<"otoño"<<endl;
        else cout<<"invierno"<<endl; break;
case 7:
case 8: cout<<"invierno"<<endl; break;
case 9: if(dia<23) cout<<"invierno"<<endl;
        else cout<<"primavera"<<endl; break;
case 10:
case 11: cout<<"primavera"<<endl; break;
case 12: if(dia<21) cout<<"primavera"<<endl;
         else cout<<"verano"<<endl; break;  
default: cout<<"Fecha inválida"<<endl; break;
    }
return 0;
}