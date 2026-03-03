#include <iostream>  
#include <string>   
using namespace std; 


struct student {
    string name;  
    int age;      
    string role;  
    string group;  
};


int main() {
    student s;  

    
    cout << "Введите имя: ";
    cin >> s.name;  

   
    cout << "Введите возраст: ";
    cin >> s.age;

    cout << "Введите роль: ";
    cin >> s.role;

   
    cout << "Введите группу: ";
    cin >> s.group;

    
    cout << "\n=== Данные студента ===" << endl;
    cout << "Имя: " << s.name << endl;
    cout << "Возраст: " << s.age << endl;
    cout << "Роль: " << s.role << endl;
    cout << "Группа: " << s.group << endl;

    return 0; 
}