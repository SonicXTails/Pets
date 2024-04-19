#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <locale>
#include <codecvt>

class Contact {
private:
    std::string name;
    std::string phoneNumber;
    std::string email;     // +
    std::string address;
    std::string birthday;

public:
    Contact(const std::string& name, const std::string& phoneNumber, const std::string& email,
        const std::string& address = "", const std::string& birthday = "")
        : name(name), phoneNumber(phoneNumber), email(email), address(address), birthday(birthday) {}

    // Геттеры для получения информации о контакте
    std::string getName() const { return name; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    std::string getBirthday() const { return birthday; }

    // Сеттеры для изменения информации о контакте
    void setName(const std::string& newName) { name = newName; }
    void setPhoneNumber(const std::string& newPhoneNumber) { phoneNumber = newPhoneNumber; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setAddress(const std::string& newAddress) { address = newAddress; }
    void setBirthday(const std::string& newBirthday) { birthday = newBirthday; }
};


class ContactManager {
private:
    std::vector<Contact> contacts;

public:
    // Функция добавления контакта
    void addContact(const Contact& newContact) {
        contacts.push_back(newContact);
    }

    // Функция удаления контакта по индексу
    void removeContact(int index) {
        if (index >= 0 && index < contacts.size()) {
            contacts.erase(contacts.begin() + index);
            std::cout << "Контакт удален успешно." << std::endl;
        }
        else {
            std::cout << "Некорректный индекс контакта." << std::endl;
        }
    }

    // Функция просмотра списка контактов
    void viewContacts() const {
        setlocale(LC_ALL, "ru_RU");
        std::cout << "Список контактов:" << std::endl;
        for (size_t i = 0; i < contacts.size(); ++i) {
            std::cout << i + 1 << ". " << contacts[i].getName() << " - " << contacts[i].getPhoneNumber() << " - " << contacts[i].getEmail() << std::endl;
        }
    }

    // Функция поиска контакта по имени или номеру телефона
    void searchContact(const std::string& searchTerm) const {
        std::cout << "Результаты поиска для '" << searchTerm << "':" << std::endl;
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.getName().find(searchTerm) != std::string::npos || contact.getPhoneNumber().find(searchTerm) != std::string::npos) {
                std::cout << "Имя: " << contact.getName() << ", Номер телефона: " << contact.getPhoneNumber() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Контакт не найден." << std::endl;
        }
    }

    // Функция сортировки списка контактов по имени
    void sortContactsByName() {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.getName() < b.getName();
            });
        std::cout << "Список контактов отсортирован по имени." << std::endl;
    }

    // Функция сортировки списка контактов по номеру телефона
    void sortContactsByPhoneNumber() {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.getPhoneNumber() < b.getPhoneNumber();
            });
        std::cout << "Список контактов отсортирован по номеру телефона." << std::endl;
    }
};


int main() {
    std::setlocale(LC_ALL, "ru_RU");

    ContactManager contactManager;

    int choice = 0;
    while (true) {
        std::cout << "\nВыберите действие:" << std::endl;
        std::cout << "1. Добавить контакт" << std::endl;
        std::cout << "2. Удалить контакт" << std::endl;
        std::cout << "3. Просмотреть список контактов" << std::endl;
        std::cout << "4. Найти контакт" << std::endl;
        std::cout << "5. Сортировать список контактов по имени" << std::endl;
        std::cout << "6. Сортировать список контактов по номеру телефона" << std::endl;
        std::cout << "7. Выйти из программы" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;


        switch (choice) {
        case 1: {
            std::string name, phoneNumber, email, address, birthday;
            std::cout << "Введите имя: ";
            std::cin >> name;
            std::cout << "Введите номер телефона: ";
            std::cin >> phoneNumber;
            std::cout << "Введите email: ";
            std::cin >> email;
            std::cout << "Введите адрес: ";
            std::cin >> address;
            std::cout << "Введите день рождения: ";
            std::cin >> birthday;
            contactManager.addContact(Contact(name, phoneNumber, email, address, birthday));
            break;
        }
        case 2: {
            int index;
            std::cout << "Введите индекс контакта для удаления: ";
            std::cin >> index;
            contactManager.removeContact(index - 1);
            break;
        }
        case 3:
            contactManager.viewContacts();
            break;
        case 4: {
            std::string searchTerm;
            std::cout << "Введите имя или номер телефона для поиска: ";
            std::cin >> searchTerm;
            contactManager.searchContact(searchTerm);
            break;
        }
        case 5:
            contactManager.sortContactsByName();
            break;
        case 6:
            contactManager.sortContactsByPhoneNumber();
            break;
        case 7:
            std::cout << "Программа завершена." << std::endl;
            return 0;
        default:
            std::cout << "Некорректный выбор. Попробуйте еще раз." << std::endl;
        }
    }
    return 0;
}