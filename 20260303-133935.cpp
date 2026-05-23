#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

using namespace std;

void logToFile(const string& message) {
    ofstream log("ball_log.txt", ios::app);
    if (log.is_open()) {
        log << message << endl;
        log.close();
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool keyPressed() {
#ifdef _WIN32
    return _kbhit();
#else
    return false;
#endif
}

char getKey() {
#ifdef _WIN32
    return _getch();
#else
    return getchar();
#endif
}

int main() {
    logToFile("Программа запущена");
    
    float pos = 0;
    float velocity = 2.5;
    float gravity = 0.3;
    float bounce = -0.9;
    int ground = 15;
    int speed = 40;
    bool running = true;
    int score = 0;
    
    while (running) {
        clearScreen();
        
        if (keyPressed()) {
            char key = getKey();
            if (key == 'q' || key == 'Q') {
                running = false;
                logToFile("Программа остановлена");
            }
            if (key == ' ') {
                velocity = 5.0;
                score++;
            }
        }
        
        int intPos = (int)pos;
        if (intPos < 0) intPos = 0;
        if (intPos > ground) intPos = ground;
        
        for (int i = 0; i < ground - intPos; i++) {
            cout << endl;
        }
        
        cout << "       O";
        cout << "  Score: " << score << endl;
        
        velocity += gravity;
        pos += velocity;
        
        if (pos >= ground) {
            pos = ground;
            velocity = velocity * bounce;
            score++;
            logToFile("Отскок от пола");
            
            if (abs(velocity) < 0.3) {
                velocity = 0;
                pos = ground;
            }
        }
        
        if (pos < 0) {
            pos = 0;
            velocity = abs(velocity) * bounce;
            logToFile("Отскок от потолка");
        }
        
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
    
    clearScreen();
    cout << "Game Over! Final score: " << score << endl;
    logToFile("Программа завершена");
    
    return 0;
}
