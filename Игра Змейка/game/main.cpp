#include <iostream>
#include <conio.h>
#include <thread>
#include <time.h>

using namespace std;

// Глобальные переменные
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, fruitBX, fruitBY, score;
int tailx[100], taily[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Прототипы функций
void Process();
void Draw();
void Input();
void Logic();
void Setup();

int main() {
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    cout << "Welcome to the game 'Snake'! " << endl;

    // Запуск игрового процесса
    Process();

    return 0;
}

// Функция для выбора уровня и запуска игры
void Process() {
    short lev;
    short speed;
    bool x = true;

    // Предложение выбора уровня
    cout << "Let's choose the level:" << endl << "(1 - Easy, 2 - Normal, 3 - Hard)" << endl;
    cin >> lev;

    // Установка скорости в зависимости от выбранного уровня
    if (lev == 1) speed = 100;
    else if (lev == 2) speed = 50;
    else if (lev == 3) speed = 10;

    // Инициализация начальных параметров игры
    Setup();

    // Основной игровой цикл
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

// Функция инициализации начальных параметров игры
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// Функция отрисовки игрового поля
void Draw() {
    // Очистка консоли
    system("cls");

    // Верхняя граница поля
    for (int i = 0; i < width + 1; i++)
        if (i == 0 || i == width)
            cout << "*";
        else
            cout << "#";
    cout << endl;

    // Основное поле
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else if (i == fruitBY && j == fruitBX)
                cout << "B";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        print = true;
                        cout << "o";
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // Нижняя граница поля
    for (int i = 0; i < width + 1; i++)
        if (i == 0 || i == width)
            cout << "*";
        else
            cout << "#";
    cout << endl;

    // Вывод счета
    cout << "Score is " << score << endl;
}

// Функция обработки ввода пользователя
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case 'p':
            dir = STOP;
            break;
        }
    }
}

// Функция обновления состояния игры
void Logic() {
    // Обновление координат головы змеи
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;

    // Обновление координат хвоста
    tailx[0] = x;
    taily[0] = y;

    // Обновление координат сегментов хвоста
    for (int i = 1; i < nTail; i++) {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Обработка направления движения головы змеи
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // Проверка столкновения с хвостом
    for (int i = 0; i < nTail; i++) {
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
    }

    // Обработка поедания фруктов
    if (x == fruitX && y == fruitY) {
        score += 5;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    if (x == fruitBX && y == fruitBY) {
        score += 10;
        fruitBX = rand() % width;
        fruitBY = rand() % height;
        nTail += 2;
    }

    // Перемещение через границы поля
    if (x >= width - 1)
        x = 0;
    else if (x < 0)
        x = width - 2;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
}
