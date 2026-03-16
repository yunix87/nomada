#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    cout <<setw(3)<<"p" <<set(4)<<"q" <<setw(89 <<2p -> q"
        <<setw(11) <<"!p || q"<<setw(12)<<"¿coincide?"<<endl;
        cout <<string(38, '-')<<endl;
        bool all_equal = true;
        for (int p = 0; p <= 1; p++) {
            for (int q = 0; q <= 1; q++) {
                bool result = (!p) || q;
                cout <<setw(3)<<p <<setw(4)<<q <<setw(8)<<result
                    <<setw(12)<<((result == ( (!p) || q)) ? "Sí" : "No")<<endl;
                if (result != ( (!p) || q)) {
                    all_equal = false;
                }
            }
        }
        
        return 0;
}