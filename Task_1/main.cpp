#include <iostream>
#include <string>
#include <Windows.h>
#include <pqxx/pqxx>
#include "C:\Users\drbo1\OneDrive\Рабочий стол\HomeWork\HomeWork_sqlcpp\Lessson_4_sqlcpp\Task_1\build\ClientBase.h"

#pragma execution_character_set("utf-8")

int main(int argc, char** argv) {
    
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    int num_action;
    std::cout << "1 - вставить клиента, 2 - вывести всех, 3 - обновить, 4 - найти, "
        "5 - добавить телефон, 6 - удаление, 0 - выход" << std::endl;
    std::cout << "Введите номер действия: ";
    std::cin >> num_action;
    try {
        BaseData BS;
        do {
            switch (num_action) {
            case 1: {
                BS.insertData();
                break;
            }
            case 2: {
                BS.selectClient();
                break;
            }
            case 3: {
                BS.updateClient();
                break;
            }
            case 4: {
                BS.findClient();
                break;
            }
            case 5: {
                BS.addPhoneClient();
                break;
            }
            case 6: {
                BS.deleteClient();
                break;
            }
            default:
                std::cout << "Нет такого действия!" << std::endl;
                break;
            }
            std::cout << "1 - вставить клиента, 2 - вывести всех, 3 - обновить, 4 - найти, "
                "5 - добавить телефон, 6 - удаление, 0 - выход" << std::endl;
            std::cout << "Введите номер действия: ";
            std::cin >> num_action;
        } while (num_action != 0);   
    }
    catch (const pqxx::sql_error& er) {
        std::cout << er.what();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what();
    }

    return 0;
}
