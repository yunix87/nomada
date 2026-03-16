#include <iostream>
using namespace std;

int main() {
    int dia, mes;
    string signo;

    cout << "Ingrese el día de nacimiento: ";
    cin >> dia;
    cout << "Ingrese el mes de nacimiento (1-12): ";
    cin >> mes;

    /*validación del día */
    if (dia < 1 || dia > 31) {
        cout << "Día inválido. Debe estar entre 1 y 31.\n";
        return 1;
    }

    switch (mes) {
        case 1:
            if (dia <= 31)
                signo = (dia <= 19) ? "Capricornio" : "Acuario";
            else
                signo = "Día inválido para enero";
            break;
        case 2:
            if (dia <= 29) 
                signo = (dia <= 18) ? "Acuario" : "Piscis";
            else
                signo = "Día inválido para febrero";
            break;
        case 3:
            if (dia <= 31)
                signo = (dia <= 20) ? "Piscis" : "Aries";
            else
                signo = "Día inválido para marzo";
            break;
        case 4:
            if (dia <= 30)
                signo = (dia <= 19) ? "Aries" : "Tauro";
            else
                signo = "Día inválido para abril";
            break;
        case 5:
            if (dia <= 31)
                signo = (dia <= 20) ? "Tauro" : "Géminis";
            else
                signo = "Día inválido para mayo";
            break;
        case 6:
            if (dia <= 30)
                signo = (dia <= 20) ? "Géminis" : "Cáncer";
            else
                signo = "Día inválido para junio";
            break;
        case 7:
            if (dia <= 31)
                signo = (dia <= 22) ? "Cáncer" : "Leo";
            else
                signo = "Día inválido para julio";
            break;
        case 8:
            if (dia <= 31)
                signo = (dia <= 22) ? "Leo" : "Virgo";
            else
                signo = "Día inválido para agosto";
            break;
        case 9:
            if (dia <= 30)
                signo = (dia <= 22) ? "Virgo" : "Libra";
            else
                signo = "Día inválido para septiembre";
            break;
        case 10:
            if (dia <= 31)
                signo = (dia <= 22) ? "Libra" : "Escorpio";
            else
                signo = "Día inválido para octubre";
            break;
        case 11:
            if (dia <= 30)
                signo = (dia <= 21) ? "Escorpio" : "Sagitario";
            else
                signo = "Día inválido para noviembre";
            break;
        case 12:
            if (dia <= 31)
                signo = (dia <= 21) ? "Sagitario" : "Capricornio";
            else
                signo = "Día inválido para diciembre";
            break;
        default:
            signo = "Mes inválido. Debe estar entre 1 y 12.";
    }

    cout << "Resultado: " << signo << endl;
    return 0;
}
