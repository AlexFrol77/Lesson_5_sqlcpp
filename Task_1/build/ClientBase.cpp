#include "ClientBase.h"


    BaseData::BaseData() : connect(
        "host = localhost "
        "port = 5432 "
        "dbname = Lesson_5_task_1 "
        "user = postgres "
        "password = Frol@1113") {
        if (connect.is_open()) {
            std::cout << "Base connect!" << std::endl;
            pqxx::work tx{ connect };
            tx.exec(createBase());
            tx.commit();
            Sleep(1000);
        }
        else {
            std::cout << "Base connect fulse!" << std::endl;
            Sleep(1000);
        }
    }

    char* BaseData::createBase() {
        sql = "CREATE TABLE IF NOT EXISTS client_base ("
            "id SERIAL primary key, "
            "first_name VARCHAR(60) null, "
            "last_name VARCHAR(60) NOT NULL, "
            "email VARCHAR(80) NULL); "

            "CREATE TABLE IF NOT EXISTS client_phone ("
            "id SERIAL primary key, "
            "id_client INTEGER references client_base(id), "
            "num_phone INTEGER NULL)";
        return sql;
    }

    void BaseData::insertData() {
        system("cls");
        pqxx::work tx{ connect };
        int phone = 0;
        std::string first_name,
            last_name,
            email;
        std::cout << "Введите имя клиента: ";
        std::cin >> first_name;
        std::cout << "Введите фамилию клиента*: ";
        std::cin >> last_name;
        std::cout << "Введите email: ";
        std::cin >> email;
        tx.exec("INSERT INTO client_base (first_name, last_name, email) "
            "VALUES ('" + tx.esc(first_name) + "', "
            "'" + tx.esc(last_name) + "', "
            "'" + tx.esc(email) + "' "
            ")");
        do {
            std::cout << "Чтобы выйти нажмите 0!" << std::endl;
            std::cout << "Введите телефон клиента: ";
            std::cin >> phone;
            if (phone != 0) {
                tx.exec("INSERT INTO client_phone (id_client, num_phone)  "
                    "VALUES ((SELECT id FROM client_base ORDER BY id DESC LIMIT 1), "
                    "'" + tx.esc(std::to_string(phone)) + "')");
            }
        } while (phone != 0);
        tx.commit();
    }
    void BaseData::addPhoneClient() {
        system("cls");
        findClient();
        pqxx::work tx{ connect };
        int sub_id = 0,
            sub_num_phone = 0;
        std::cout << "Введите ID клиента для добавления телефонного номера: ";
        std::cin >> sub_id;
        std::cout << "Введите номер телефона который хотите добавить клиенту: ";
        std::cin >> sub_num_phone;
        tx.exec("INSERT INTO client_phone(id_client, num_phone) "
            "VALUES ('" + tx.esc(std::to_string(sub_id)) + "', '" + tx.esc(std::to_string(sub_num_phone)) + "')");
        tx.commit();
    }
    void BaseData::selectClient() {
        system("cls");
        pqxx::work tx{ connect };
        std::string num_collum;
        for (auto [id_client, last_name, first_name, email, id_phone, phone] :
            tx.query<int, std::string, std::string, std::string, int, int>(
                "SELECT client_base.id, last_name, first_name, email, client_phone.id, num_phone FROM client_base "
                "JOIN client_phone ON client_base.id = client_phone.id_client"))
        {
            std::cout << "| ID клиента: |" << id_client << "| Имя: |" << first_name << "| Фамилия: |" << last_name
                << "| Email: |" << email << "| ID телефона: |" << id_phone << "| Телефон: |" << phone << std::endl;
        }
    }
    void BaseData::findClient() {
        
        system("cls");
        int action = 0;
        std::cout << "Если Вы хотите искать по Имени или Фамилии или Email наж 1" << std::endl;
        std::cout << "Если Вы хотите искать по ID клиента или по номеру телефона наж 2" << std::endl;
        std::cin >> action;
        if (action == 1) {
            printFindStrClient();
        }
        else if (action == 2) {
            printFindIntClient();
        }
        else {
            std::cout << "Нет такого действия!" << std::endl;
        }
        pqxx::work tx{ connect };
        tx.commit();
    }

    void BaseData::updateClient() {
        system("cls");
        int id_client = 0,
            num_collum = 0;
        std::string changed_str;
        findClient();
        pqxx::work tx{ connect };
        std::cout << "Введите ID клиента: ";
        std::cin >> id_client;
        std::cout << "Заменить имя наж 1, заменить фамилию наж 2, "
            "заменить email наж 3, изменить телефон - 4" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> num_collum;
        if (num_collum == 1) {
            std::cout << "Введите новое имя: ";
            std::cin >> changed_str;
            tx.exec("UPDATE client_base SET first_name = '" + tx.esc(changed_str) + "'"
                "WHERE client_base.id = '" + tx.esc(std::to_string(id_client)) + "' ");
        }
        else if (num_collum == 2) {
            std::cout << "Введите новую фамилию: ";
            std::cin >> changed_str;
            tx.exec("UPDATE client_base SET last_name = '" + tx.esc(changed_str) + "'"
                "WHERE client_base.id = '" + tx.esc(std::to_string(id_client)) + "' ");
        }
        else if (num_collum == 3) {
            std::cout << "Введите новый email: ";
            std::cin >> changed_str;
            tx.exec("UPDATE client_base SET email = '" + tx.esc(changed_str) + "'"
                "WHERE client_base.id = '" + tx.esc(std::to_string(id_client)) + "' ");
        }
        else if (num_collum == 4) {
            int id_phone = 0,
                chg_num_phone = 0;
            std::cout << "Введите ID телефона который изменяете: ";
            std::cin >> id_phone;
            std::cout << "Введите новый номер телефона: ";
            std::cin >> chg_num_phone;;
            tx.exec("UPDATE client_phone SET num_phone = '" + tx.esc(std::to_string(chg_num_phone)) + "'"
                "WHERE client_phone.id = '" + tx.esc(std::to_string(id_phone)) + "' ");
        }
        else {
            std::cout << "Нет такого поля!";
            Sleep(1000);
        }
        tx.commit();
    }
    void BaseData::deleteClient() {
        system("cls");
        int sub_action = 0;
        bool flag = true;
        findClient();
        pqxx::work tx{ connect };
        std::cout << "Удалить клиента наж 1, удалить номер телефона наж 2, отменить удаление наж 0: ";
        std::cin >> sub_action;
        if (sub_action == 1) {
            int sub_id_phone = 0;
            std::cout << "Введите ID клиента которого хотите удалить: ";
            std::cin >> sub_id_phone;
            tx.exec("DELETE FROM client_phone "
                "WHERE client_phone.id_client = '" + tx.esc(std::to_string(sub_id_phone)) + "' ");
            flag = true;
        }
        else if (sub_action == 2) {
            int sub_id_phone = 0;
            std::cout << "Введите ID телефона который хотите удалить: ";
            std::cin >> sub_id_phone;
            tx.exec("DELETE FROM client_phone "
                "WHERE client_phone.id = '" + tx.esc(std::to_string(sub_id_phone)) + "' ");
            flag = true;
        }
        else {
            std::cout << "Нет такого действия!" << std::endl;
            Sleep(1000);
        }
        tx.commit();
    }
  
    void BaseData::printFindStrClient() {
        pqxx::work tx{ connect };
        std::string sub_str_client;
        std::cout << "Введите Имя или Фамилию или email клиента : ";
        std::cin >> sub_str_client;
        for (auto [id, first_name, last_name, email, id_phone, num_phone] :
            tx.query <int, std::string, std::string, std::string, int, int>
            ("SELECT cb.id, cb.first_name, cb.last_name, cb.email, "
                "cp.id, cp.num_phone FROM client_base AS cb "
                "JOIN client_phone AS cp ON cb.id = cp.id_client "
                "WHERE cb.last_name = '" + tx.esc(sub_str_client) + "' "
                "OR cb.first_name = '" + tx.esc(sub_str_client) + "' "
                "OR cb.email = '" + tx.esc(sub_str_client) + "'; "))
        {
            std::cout << "ID клиента: " << id << " Имя: " << first_name <<
                " Фамилия: " << last_name << " Email: " << email << " ID Телефона: " << id_phone
                << " Телефон: " << num_phone << std::endl;
        }
        tx.commit();
    }
    void BaseData::printFindIntClient() {
        pqxx::work tx{ connect };
        std::string sub_int_client;
        std::cout << "Введите ID клиента или номер телефона клиента: ";
        std::cin >> sub_int_client;
        for (auto [id, first_name, last_name, email, id_phone, num_phone] :
            tx.query <int, std::string, std::string, std::string, int, int>
            ("SELECT cb.id, cb.first_name, cb.last_name, cb.email, "
                "cp.id, cp.num_phone FROM client_base AS cb "
                "JOIN client_phone AS cp ON cb.id = cp.id_client "
                "WHERE cb.id = '" + tx.esc(sub_int_client) + "' "
                "OR cp.num_phone = '" + tx.esc(sub_int_client) + "' "))
                
        {
            std::cout << "ID клиента: " << id << " Имя: " << first_name <<
                " Фамилия: " << last_name << " Email: " << email << " ID Телефона: " << id_phone
                << " Телефон: " << num_phone << std::endl;
        }
        tx.commit();
    }