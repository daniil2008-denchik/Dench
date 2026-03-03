#include <iostream>
using namespace std;


struct Distance {
    double metry;  
    int shagi;    
};

int main() {
    Distance d1, d2, sum; 

 
    cout << "Первая дистанция. Сколько метров? ";
    cin >> d1.metry;
    cout << "Первая дистанция. Сколько шагов? ";
    cin >> d1.shagi;

 
    cout << "Вторая дистанция. Сколько метров? ";
    cin >> d2.metry;
    cout << "Вторая дистанция. Сколько шагов? ";
    cin >> d2.shagi;

    // Складываем
    sum.metry = d1.metry + d2.metry;  
    sum.shagi = d1.shagi + d2.shagi; 


    cout << "\n=== Сумма дистанций ===" << endl;
    cout << "Всего метров: " << sum.metry << endl;
    cout << "Всего шагов: " << sum.shagi << endl;

    return 0;
}