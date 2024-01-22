#include <iostream>

const int ROWS = 4;
const int COLS = 4;

// Функция для вывода игрового поля
void printField(const int field[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;

        for (int j = 0; j < COLS; ++j) {
            std::cout << "| " << field[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }

    for (int j = 0; j < COLS; ++j) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}

// Рекурсивная функция для проверки, равна ли сумма элементов массива 100
bool isSum100(const int array[], int size, int currentIndex, int currentSum) {
    // Базовый случай: достигнут конец массива
    if (currentIndex == size) {
        return currentSum == 100;
    }

    // Рекурсивный случай: добавляем текущий элемент к сумме и переходим к следующему
    return isSum100(array, size, currentIndex + 1, currentSum + array[currentIndex]) ||
        isSum100(array, size, currentIndex + 1, currentSum);
}

// Функция для проверки суммы в каждой строке и каждом столбце
int checkRowsAndColumns(const int field[ROWS][COLS]) {
    // Переменная для хранения количества ошибок
    int errorsCount = 0;

    // Проверка суммы в каждой строке
    for (int i = 0; i < ROWS; ++i) {
        if (!isSum100(field[i], COLS, 0, 0)) {
            std::cout << "Сумма чисел строки " << i + 1 << " не равна 100." << std::endl;
            errorsCount++;
        }
    }

    // Проверка суммы в каждом столбце
    for (int j = 0; j < COLS; ++j) {
        int column[ROWS];
        for (int i = 0; i < ROWS; ++i) {
            column[i] = field[i][j];
        }

        if (!isSum100(column, ROWS, 0, 0)) {
            std::cout << "Сумма чисел столбца " << j + 1 << " не равна 100." << std::endl;
            errorsCount++;
        }
    }

    return errorsCount;
}

int main() {
    setlocale(LC_ALL, "RU"); // Установка русской локали
    bool gameOver = false;

    // Инициализация начального поля
    int myField[4][4] = { {7, 8, 4, 9}, {9, 4, 2, 4}, {9, 1, 7, 4}, {3, 3, 2, 3} };

    while (!gameOver) {
        // Проверка условия завершения игры
        if (checkRowsAndColumns(myField) == 0) {
            // Вывод поля и поздравительного сообщения
            printField(myField);
            std::cout << "Вы выиграли! Сумма всех строк и столбцов равна ста!" << std::endl;

            char f;
            std::cin >> f; // Чтобы программа не закрывалась сразу после вывода поздравления
            gameOver = true;
        }

        // Вывод текущего состояния поля
        std::cout << std::endl;
        std::cout << "Игровое поле:" << std::endl;
        printField(myField);

        // Ввод данных от пользователя
        int rowIndex, colIndex, additionalDigit;
        std::cout << std::endl;
        std::cout << "Введите номер ряда (1-" << ROWS << "): ";
        std::cin >> rowIndex;
        std::cout << "Введите номер столбца (1-" << COLS << "): ";
        std::cin >> colIndex;
        std::cout << "Введите цифру для добавления: ";
        std::cin >> additionalDigit;

        // Проверка введенных индексов на корректность
        if (rowIndex >= 1 && rowIndex <= ROWS && colIndex >= 1 && colIndex <= COLS) {
            // Добавление цифры в ячейку
            myField[rowIndex - 1][colIndex - 1] = myField[rowIndex - 1][colIndex - 1] * 10 + additionalDigit;
        }
        else {
            std::cout << "Неверные номера, попробуйте снова." << std::endl;
            continue; // Пропустить остаток цикла и начать следующую итерацию
        }

        // Очистка консоли
        std::cout << std::endl;
        system("cls");
    }

    return 0;
}
