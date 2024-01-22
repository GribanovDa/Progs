#include <iostream>
#include <conio.h>
#include <thread>
#include <time.h>

using namespace std;

// ���������� ����������
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, fruitBX, fruitBY, score;
int tailx[100], taily[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// ��������� �������
void Process();
void Draw();
void Input();
void Logic();
void Setup();

int main() {
    // ������������� ���������� ��������� �����
    srand(time(NULL));
    cout << "Welcome to the game 'Snake'! " << endl;

    // ������ �������� ��������
    Process();

    return 0;
}

// ������� ��� ������ ������ � ������� ����
void Process() {
    short lev;
    short speed;
    bool x = true;

    // ����������� ������ ������
    cout << "Let's choose the level:" << endl << "(1 - Easy, 2 - Normal, 3 - Hard)" << endl;
    cin >> lev;

    // ��������� �������� � ����������� �� ���������� ������
    if (lev == 1) speed = 100;
    else if (lev == 2) speed = 50;
    else if (lev == 3) speed = 10;

    // ������������� ��������� ���������� ����
    Setup();

    // �������� ������� ����
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

// ������� ������������� ��������� ���������� ����
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// ������� ��������� �������� ����
void Draw() {
    // ������� �������
    system("cls");

    // ������� ������� ����
    for (int i = 0; i < width + 1; i++)
        if (i == 0 || i == width)
            cout << "*";
        else
            cout << "#";
    cout << endl;

    // �������� ����
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

    // ������ ������� ����
    for (int i = 0; i < width + 1; i++)
        if (i == 0 || i == width)
            cout << "*";
        else
            cout << "#";
    cout << endl;

    // ����� �����
    cout << "Score is " << score << endl;
}

// ������� ��������� ����� ������������
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

// ������� ���������� ��������� ����
void Logic() {
    // ���������� ��������� ������ ����
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;

    // ���������� ��������� ������
    tailx[0] = x;
    taily[0] = y;

    // ���������� ��������� ��������� ������
    for (int i = 1; i < nTail; i++) {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // ��������� ����������� �������� ������ ����
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

    // �������� ������������ � �������
    for (int i = 0; i < nTail; i++) {
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
    }

    // ��������� �������� �������
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

    // ����������� ����� ������� ����
    if (x >= width - 1)
        x = 0;
    else if (x < 0)
        x = width - 2;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
}
