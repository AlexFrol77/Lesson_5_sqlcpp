#pragma once
#include <iostream>
#include <Windows.h>
#include <pqxx/pqxx>

#pragma execution_character_set("utf-8")

class BaseData {
public:

    BaseData();
    char* createBase();

    void insertData();
    void addPhoneClient();
    void selectClient();
    void findClient();
    void updateClient();
    void deleteClient();
    void printFindStrClient();
    void printFindIntClient();

private:
    char* sql;
    pqxx::connection connect;
};