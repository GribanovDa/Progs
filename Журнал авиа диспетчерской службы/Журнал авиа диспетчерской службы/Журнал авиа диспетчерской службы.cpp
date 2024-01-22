#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <fstream>

class TCharArray {
private:
    char* buf; // буфер для хранения символов
    size_t len; // длина строки

public:
    const char* get() const; // метод для получения указателя на строку
    const size_t length() const; // метод для получения длины строки
    void set(const char* str); // метод для установки нового значения строки
    char& operator[](int index); // перегрузка оператора доступа к символу по индексу
    char& at(int index); // метод для доступа к символу по индексу с проверкой границ

    TCharArray(); // конструктор по умолчанию
    TCharArray(const char* str); // конструктор с инициализацией строки
    TCharArray(const TCharArray& other); // конструктор копирования
    ~TCharArray(); // деструктор
};

const char* TCharArray::get() const {
    return buf; // возвращаем указатель на строку
}

const size_t TCharArray::length() const {
    return len; // возвращаем длину строки
}

void TCharArray::set(const char* str) {
    delete[] buf; // освобождаем память от предыдущего содержимого
    len = strlen(str); // определяем длину новой строки
    buf = new char[len + 1]; // выделяем память под новую строку
    strcpy(buf, str); // копируем новую строку в буфер
}

char& TCharArray::operator[](int index) {
    return buf[index]; // возвращаем символ по указанному индексу
}

char& TCharArray::at(int index) {
    if (index < 0 || index >= len) { // проверяем выход за границы строки
        throw std::out_of_range("Index out of range"); // выбрасываем исключение при выходе за границы
    }
    return buf[index]; // возвращаем символ по указанному индексу
}

TCharArray::TCharArray() : buf(nullptr), len(0) {} // конструктор по умолчанию

TCharArray::TCharArray(const char* str) : len(strlen(str)) { // конструктор с инициализацией строки
    buf = new char[len + 1]; // выделяем память под строку
    strcpy(buf, str); // копируем строку в буфер
}

TCharArray::TCharArray(const TCharArray& other) : len(other.len) { // конструктор копирования
    buf = new char[len + 1]; // выделяем память под новую строку
    strcpy(buf, other.buf); // копируем содержимое другой строки в новую
}

TCharArray::~TCharArray() {
    delete[] buf; // освобождаем выделенную память при уничтожении объекта
}

class String : public TCharArray {
public:
    // Перегрузка оператора присваивания для класса String
    String& operator=(const String&);

    // Дружественные функции вывода и ввода для класса String
    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream&, String&);

    // Перегрузка оператора сложения для конкатенации строк
    String operator+(const String& other) const;

    // Перегрузка операторов сравнения для строк
    bool operator==(const String& other) const;
    bool operator>(const String& other) const;
    bool operator<(const String& other) const;
    bool operator!=(const String& other) const;

    // Конструктор по умолчанию
    String();

    // Конструктор с параметром - строкой char*
    String(const char*);

    // Конструктор копирования
    String(const String&);

    // Деструктор
    ~String();

    // Метод получения указателя на строку
    const char* get() const {
        return TCharArray::get();
    }

    // Метод получения длины строки
    const size_t length() const {
        return TCharArray::length();
    }
};

// Перегрузка оператора вывода для класса String
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.get();
    return os;
}

// Перегрузка оператора ввода для класса String
std::istream& operator>>(std::istream& is, String& str) {
    char buffer[4096];
    is >> buffer;
    str = String(buffer);
    return is;
}

// Перегрузка оператора сложения для конкатенации строк
String String::operator+(const String& other) const {
    String result;
    size_t newLen = length() + other.length();

    // Выделение памяти под новую строку
    char* newBuf = new char[newLen + 1];

    // Копирование текущей строки в новый буфер
    strcpy(newBuf, get());

    // Конкатенация строки other к текущей строке
    strcat(newBuf, other.get());

    // Установка нового буфера в объект result
    result.set(newBuf);

    // Освобождение выделенной памяти
    delete[] newBuf;

    return result;
}

// Конструктор по умолчанию
String::String() : TCharArray() {}

// Конструктор с параметром - строкой char*
String::String(const char* str) : TCharArray(str) {}

// Конструктор копирования
String::String(const String& other) : TCharArray(other) {}

// Деструктор
String::~String() {}

// Перегрузка оператора присваивания для класса String
String& String::operator=(const String& other) {
    // Проверка на самоприсваивание
    if (this == &other) {
        return *this;
    }

    // Установка нового значения из другой строки
    TCharArray::set(other.get());

    return *this;
}

class Tour {
private:
    String name;
    String country;
    double cost;
    int duration;
    String transportation;

public:
    // Конструктор по умолчанию и конструктор с параметрами
    Tour() : name(""), country(""), cost(0.0), duration(0), transportation("") {}
    Tour(const char* name, const char* country, double cost, int duration, const char* transportation)
        : name(name), country(country), cost(cost), duration(duration), transportation(transportation) {}

    // Методы доступа к приватным полям класса
    const char* getName() const {
        return name.get();
    }
    void setName(const char* name) {
        this->name = name;
    }

    const char* getCountry() const {
        return country.get();
    }
    void setCountry(const char* country) {
        this->country = country;
    }

    double getCost() const {
        return cost;
    }
    void setCost(double cost) {
        this->cost = cost;
    }

    int getDuration() const {
        return duration;
    }
    void setDuration(int duration) {
        this->duration = duration;
    }

    const char* getTransportation() const {
        return transportation.get();
    }
    void setTransportation(const char* transportation) {
        this->transportation = transportation;
    }

    // Дружественные функции вывода и ввода для класса Tour
    friend std::ostream& operator<<(std::ostream& os, const Tour& tour);
    friend std::istream& operator>>(std::istream& is, Tour& tour);
};

std::istream& operator>>(std::istream& is, Tour& tour) {
    size_t nameLen, countryLen, transportLen;

    is.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    if (nameLen < 0 || nameLen > 255) {
        return is;
    }
    char* nameBuf = new char[nameLen + 1];
    is.read(nameBuf, nameLen);
    nameBuf[nameLen] = '\0';
    tour.setName(nameBuf);
    delete[] nameBuf;

    is.read(reinterpret_cast<char*>(&countryLen), sizeof(countryLen));
    if (countryLen < 0 || countryLen > 255) {
        return is;
    }
    char* countryBuf = new char[countryLen + 1];
    is.read(countryBuf, countryLen);
    countryBuf[countryLen] = '\0';
    tour.setCountry(countryBuf);
    delete[] countryBuf;

    is.read(reinterpret_cast<char*>(&tour.cost), sizeof(tour.cost));
    is.read(reinterpret_cast<char*>(&tour.duration), sizeof(tour.duration));

    is.read(reinterpret_cast<char*>(&transportLen), sizeof(transportLen));
    if (transportLen < 0 || transportLen > 255) {
        return is;
    }
    char* transportBuf = new char[transportLen + 1];
    is.read(transportBuf, transportLen);
    transportBuf[transportLen] = '\0';
    tour.setTransportation(transportBuf);
    delete[] transportBuf;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Tour& tour) {
    size_t nameLen = tour.name.length();
    os.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    os.write(tour.name.get(), nameLen);

    size_t countryLen = tour.country.length();
    os.write(reinterpret_cast<const char*>(&countryLen), sizeof(countryLen));
    os.write(tour.country.get(), countryLen);

    os.write(reinterpret_cast<const char*>(&tour.cost), sizeof(tour.cost));
    os.write(reinterpret_cast<const char*>(&tour.duration), sizeof(tour.duration));

    size_t transportLen = tour.transportation.length();
    os.write(reinterpret_cast<const char*>(&transportLen), sizeof(transportLen));
    os.write(tour.transportation.get(), transportLen);

    return os;
}

void printHelp() {
    std::cout << "База данных экскурсионного бюро\n" << std::endl;
    std::cout << "Использование:" << std::endl;
    std::cout << "--help или -h: Вывести справку о программе и завершить работу." << std::endl;
    std::cout << "-c [N] [file_name]: Создать массив из N записей в файле file_name." << std::endl;
    std::cout << "-r [N] [file_name]: Прочитать и вывести N записей из файла file_name." << std::endl;
    std::cout << "-e [N] [file_name]: Редактировать N-ую запись в файле file_name." << std::endl;
    std::cout << "-a [N] [file_name]: Добавить N записей в конец файла file_name." << std::endl;
}

void createTours(int N, const std::string& file_name) {
    Tour* tours = new Tour[N];

    for (int i = 0; i < N; i++) {
        std::string name;
        std::string country;
        double cost;
        int duration;
        std::string transportation;

        std::cout << "Тур " << i + 1 << ".\n";

        std::cout << "Наименование тура: ";
        std::getline(std::cin, name);

        std::cout << "Страна: ";
        std::getline(std::cin, country);

        std::cout << "Стоимость: ";
        std::cin >> cost;

        std::cout << "Продолжительность: ";
        std::cin >> duration;

        std::cout << "Вид транспорта: ";
        std::cin.ignore();
        std::getline(std::cin, transportation);

        std::cout << "__________________________________________\n";

        Tour newItem(name.c_str(), country.c_str(), cost, duration, transportation.c_str());
        tours[i] = newItem;
    }

    std::ofstream outFile(file_name, std::ios::binary);
    if (!outFile.is_open()) {
        std::cout << "Не удалось открыть файл " << file_name << " для записи." << std::endl;
        delete[] tours;
        return;
    }

    for (int i = 0; i < N; i++) {
        outFile << tours[i];
    }

    outFile.close();
    delete[] tours;
    std::cout << "Создан файл " << file_name << " с " << N << " записями." << std::endl;
}

void readTours(int N, const std::string& file_name) {
    std::ifstream inFile(file_name, std::ios::binary);
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл " << file_name << " для чтения." << std::endl;
        return;
    }

    Tour* tours = new Tour[N];
    int count = 0;
    while (count < N && inFile >> tours[count]) {
        count++;
    }

    inFile.close();
    if (count < N) {
        std::cout << "Количество записей в файле меньше " << N << std::endl;
        delete[] tours;
        return;
    }

    for (int i = 0; i < N; ++i) {
        std::cout << "Запись " << i + 1 << ".\n";
        std::cout << "Наименование тура: " << tours[i].getName() << "\n";
        std::cout << "Страна: " << tours[i].getCountry() << "\n";
        std::cout << "Стоимость: " << tours[i].getCost() << "\n";
        std::cout << "Продолжительность: " << tours[i].getDuration() << "\n";
        std::cout << "Вид транспорта: " << tours[i].getTransportation() << "\n";
        std::cout << "-----\n";
    }

    delete[] tours;
}

void editTour(int N, const std::string& file_name) {

    std::fstream file(file_name, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл " << file_name << " для редактирования." << std::endl;
        return;
    }

    Tour* tours = nullptr;
    int count = 0;

    while (!file.eof()) {
        Tour newItem;
        if (file >> newItem) {
            Tour* temp = new Tour[count + 1];
            for (int i = 0; i < count; ++i) {
                temp[i] = tours[i];
            }
            temp[count] = newItem;
            delete[] tours;
            tours = temp;
            count++;
        }
    }

    file.close();

    if (N <= 0 || N > count) {
        std::cout << "Неправильный номер записи для редактирования." << std::endl;
        delete[] tours;
        return;
    }

    std::string name;
    std::string country;
    double cost;
    int duration;
    std::string transportation;

    std::cout << "Тур " << N << ".\n";

    std::cout << "Наименование тура: ";
    std::getline(std::cin, name);

    std::cout << "Страна: ";
    std::getline(std::cin, country);

    std::cout << "Стоимость: ";
    std::cin >> cost;

    std::cout << "Продолжительность: ";
    std::cin >> duration;

    std::cout << "Вид транспорта: ";
    std::cin.ignore();
    std::getline(std::cin, transportation);

    std::cout << "__________________________________________\n";

    Tour newItem(name.c_str(), country.c_str(), cost, duration, transportation.c_str());

    tours[N - 1] = newItem;

    std::ofstream outFile(file_name, std::ios::binary);
    if (!outFile.is_open()) {
        std::cout << "Не удалось открыть файл " << file_name << " для записи." << std::endl;
        delete[] tours;
        return;
    }

    for (int i = 0; i < count; ++i) {
        outFile << tours[i];
    }

    outFile.close();

    delete[] tours;

    std::cout << "Запись номер " << N << " успешно отредактирована в файле " << file_name << "." << std::endl;
}


void addTours(int N, const std::string& file_name) {
    std::ofstream outFile(file_name, std::ios::binary | std::ios::app);
    if (!outFile.is_open()) {
        std::cout << "Не удалось открыть файл " << file_name << " для записи." << std::endl;
        return;
    }

    Tour* tours = new Tour[N];

    for (int i = 0; i < N; i++) {
        std::string name;
        std::string country;
        double cost;
        int duration;
        std::string transportation;

        std::cout << "Тур " << i + 1 << ".\n";

        std::cout << "Наименование тура: ";
        std::getline(std::cin, name);

        std::cout << "Страна: ";
        std::getline(std::cin, country);

        std::cout << "Стоимость: ";
        std::cin >> cost;

        std::cout << "Продолжительность: ";
        std::cin >> duration;

        std::cout << "Вид транспорта: ";
        std::cin.ignore();
        std::getline(std::cin, transportation);

        std::cout << "__________________________________________\n";

        Tour newItem(name.c_str(), country.c_str(), cost, duration, transportation.c_str());
        tours[i] = newItem;
    }

    for (int i = 0; i < N; i++) {
        outFile << tours[i];
    }

    outFile.close();

    delete[] tours;

    std::cout << "Добавлено " << N << " записей в файл " << file_name << "." << std::endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc == 1) {
        std::cout << "Не указаны аргументы запуска. Используйте --help для получения справки." << std::endl;
        return 1;
    }

    std::string option = argv[1];

    if (option == "--help" || option == "-h") {
        printHelp();
        return 0;
    }

    if (option == "-c") {
        if (argc != 4) {
            std::cout << "Неправильное количество аргументов. Используйте --help для получения справки." << std::endl;
            return 1;
        }

        int N = std::stoi(argv[2]);
        std::string file_name = argv[3];

        createTours(N, file_name);

        return 0;
    }


    if (option == "-r") {
        if (argc != 4) {
            std::cout << "Неправильное количество аргументов. Используйте --help для получения справки." << std::endl;
            return 1;
        }

        int N = std::stoi(argv[2]);
        std::string file_name = argv[3];

        readTours(N, file_name);

        return 0;
    }

    if (option == "-e") {
        if (argc != 4) {
            std::cout << "Неправильное количество аргументов. Используйте --help для получения справки." << std::endl;
            return 1;
        }

        int N = std::stoi(argv[2]);
        std::string file_name = argv[3];

        editTour(N, file_name);

        return 0;
    }

    if (option == "-a") {
        if (argc != 4) {
            std::cout << "Неправильное количество аргументов. Используйте --help для получения справки." << std::endl;
            return 1;
        }

        int N = std::stoi(argv[2]);
        std::string file_name = argv[3];

        addTours(N, file_name);

        return 0;
    }

}