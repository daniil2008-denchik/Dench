#include <iostream>
using namespace std;


struct MoeChislo {
    int a;  
    int b;  
};


MoeChislo add(MoeChislo x, MoeChislo y) {
    MoeChislo r;          
    r.a = x.a + y.a;      
    r.b = x.b + y.b;     
    return r;            
}

int main() {
    MoeChislo num1, num2, result;  


    cout << "Введите первую часть первого числа: ";
    cin >> num1.a;
    cout << "Введите вторую часть первого числа: ";
    cin >> num1.b;


    cout << "Введите первую часть второго числа: ";
    cin >> num2.a;
    cout << "Введите вторую часть второго числа: ";
    cin >> num2.b;

    result = add(num1, num2);


    cout << "\nРезультат сложения: " << result.a << " + " << result.b << endl;

    return 0;
}