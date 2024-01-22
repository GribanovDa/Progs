#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_map>

std::string KEY("secret");

// Структура для представления пользователя
struct User {
    std::string name;
    std::string group;
    std::string encryptedPassword; // Зашифрованный пароль
};

// Класс, представляющий систему учета пользователей
class UserAccountSystem {
private:
    std::vector<User> users; // Вектор для хранения пользователей

    // Метод для шифрования пароля (пример простого шифрования)
    std::string encryptPassword(const std::string& password, const std::string& key) {
        std::string encrypted;
        for (size_t i = 0; i < password.length(); ++i) {
            encrypted += password[i] ^ key[i % key.length()]; // Используем XOR для шифрования
        }
        return encrypted;
    }


public:
    // Метод для добавления нового пользователя
    void addUser(const std::string& name, const std::string& group, const std::string& password) {
        User newUser;
        newUser.name = name;
        newUser.group = group;
        newUser.encryptedPassword = encryptPassword(password, KEY);
        users.push_back(newUser);
    }

    // Метод для сохранения пользователей в файл
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename, std::ofstream::trunc);
        if (file.is_open()) {
            for (const auto& user : users) {
                file << user.name << "\n" << user.group << "\n" << user.encryptedPassword << "\n";
            }
            file.close();
            std::cout << "Пользователи сохранены в файл: " << filename << std::endl;
        }
        else {
            std::cerr << "Не удалось открыть файл для сохранения." << std::endl;
        }

    }

    // Метод для загрузки пользователей из файла
    void loadFromFile(const std::string& filename) {
        users.clear(); // Очистить текущий список пользователей

        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (!file.eof()) {
                std::string name, group, encryptedPassword;
                file >> name;
                if (name == "")
                {
                    continue;
                }
                file >> group;
                file >> encryptedPassword;
                User user;
                user.name = name;
                user.group = group;
                user.encryptedPassword = encryptedPassword;

                users.push_back(user);
            }
            file.close();
            //std::cout << "Пользователи загружены из файла: " << filename << std::endl;
        }
        else {
            std::cerr << "Не удалось открыть файл для загрузки." << std::endl;
        }
    }

    std::string getGroup(const std::string& name, const std::string& password) {
        for (const auto& user : users) {
            if (user.name == name && user.encryptedPassword == encryptPassword(password, KEY)) {
                return "Студент " + user.name + " учится в группе " + user.group;
            }
        }
        return "Студент не найдтен или неправильный пароль";
    }

    void print() {
        std::cout << "Список пользователей:" << std::endl;
        for (const auto& user : users) {
            std::cout << "Имя: " << user.name << ", Группа: " << user.group << std::endl;
        }
    }

    void removeUser(const std::string& name) {
        auto it = std::remove_if(users.begin(), users.end(), [&name](const User& user) {
            return user.name == name;
            });
        users.erase(it, users.end());
    }
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc == 3) {
        if (strcmp(argv[1], "admin") == 0 && strcmp(argv[2], "123123") == 0) {
            UserAccountSystem s;
            int mode = 0;
            while (mode != 3)
            {
                s.loadFromFile("users.cfg");
                s.print();
                std::cout << "1 - Добавить студента\n2 - Удалить студента\n3 - Выход\n";
                std::cin >> mode;
                if (mode == 1)
                {
                    std::cout << "Введите имя, группу и пароль стундета\n";
                    std::string name, group, pass;
                    std::cin >> name >> group >> pass;
                    s.addUser(name, group, pass);
                }
                if (mode == 2)
                {
                    std::cout << "Введите имя студента которого хотите удалить из системы\n";
                    std::string name;
                    std::cin >> name;
                    s.removeUser(name);
                }
                s.saveToFile("users.cfg");
            }

        }
        else
        {
            std::cout << "Ошибка! Неправильный пароль для входа в режим конфигурирования!\n";
        }
    }

    UserAccountSystem s;

    while (true)
    {
        s.loadFromFile("users.cfg");
        std::cout << "<<INPUT>> ";
        std::string inputName, inputPass;
        std::cin >> inputName >> inputPass;
        std::cout << "<<OUTPUT>> " << s.getGroup(inputName, inputPass) << "\n";
    }

    return 0;
}