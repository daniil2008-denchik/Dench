#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

// Функция очистки экрана
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Функция задержки (мс)
void delay(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

// Рисование человечка
void draw(int pos) {
    // Пустые строки (позиция)
    for (int i = 0; i < pos; i++) {
        cout << endl;
    }
    
    // Человечек
    cout << "   O" << endl;
    cout << "  /|\\" << endl;
    cout << "  / \\" << endl;
    
    // Пол внизу
    if (pos <= 1) {
        cout << endl << "   ===" << endl;
    }
}

int main() {
    // ПРОСТЫЕ ПЕРЕМЕННЫЕ
    int pos = 0;           // позиция (0 = низ, 10 = верх)
    int dir = 1;           // направление (1 = вверх, -1 = вниз)
    bool paused = false;   // пауза
    int counter = 0;       // счётчик прыжков
    
    const int MAX = 10;    // максимальная высота
    
    cout << "Прыгающий человечек" << endl;
    cout << "Управление: p - пауза, r - сброс, q - выход" << endl;
    cout << "----------------------------------------" << endl;
    
    // ГЛАВНЫЙ ЦИКЛ
    while (true) {
        // Очищаем экран
        clearScreen();
        
        // Показываем информацию
        cout << "Position: " << pos << " | ";
        cout << "Jumping: " << counter << " | ";
        cout << "Status: " << (dir == 1 ? "Verh" : "Vniz") << endl;
        cout << "----------------------------------------" << endl;
        
        // Рисуем человечка
        draw(pos);
        
        // ФИЗИКА (только если не на паузе)
        if (!paused) {
            // Двигаемся всегда на 1 (постоянная скорость)
            pos = pos + dir;
            
            // Проверка границ
            if (pos >= MAX) {
                pos = MAX;
                dir = -1;  // летим вниз
            }
            else if (pos <= 0) {
                pos = 0;
                dir = 1;   // летим вверх
                counter++; // увеличиваем счётчик прыжков
            }
        }
        
        // ЗАДЕРЖКА (50 мс = постоянная скорость)
        delay(50);
        
        // ПРОВЕРКА КЛАВИШ (без ожидания)
        #ifdef _WIN32
            if (GetAsyncKeyState('P') & 0x8000) {
                paused = !paused;
                delay(200); // защита от множественного нажатия
            }
            if (GetAsyncKeyState('R') & 0x8000) {
                pos = 0;
                dir = 1;
                counter = 0;
                paused = false;
                delay(200);
            }
            if (GetAsyncKeyState('Q') & 0x8000) {
                break;
            }
        #else
            // Для Linux - упрощённая версия без проверки клавиш
            // (нужно нажимать Enter после команд)
            char key;
            if (kbhit()) {
                key = getchar();
                if (key == 'p' || key == 'P') {
                    paused = !paused;
                }
                if (key == 'r' || key == 'R') {
                    pos = 0;
                    dir = 1;
                    counter = 0;
                    paused = false;
                }
                if (key == 'q' || key == 'Q') {
                    break;
                }
            }
        #endif
    }
    
    cout << "\nИгра завершена!" << endl;
    cout << "Всего прыжков: " << counter << endl;
    
    return 0;
}
