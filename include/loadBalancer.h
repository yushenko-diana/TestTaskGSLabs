#pragma once
#include <iostream>
#include "server.h"
#include <vector>

/**
 * @brief Класс, описывающий балансировщик нагрузки
 */
class LoadBalancer {

public:
    /**
     * @brief Конструктор
     * @param [const vector<string>&]destinationAddresses. Адрес отправки датаграмм
     * @param [int]port. Порт отправки датаграмм
     */
    LoadBalancer(const std::vector<std::string>& destinationAddresses);
    /**
     * @brief Функция балансировки нагрузки
     * @param [const Server&]server. Объект сервера
     * @param [const char*]buffer. Датаграмма
     * @param [int]size. Размер датаграммы
     * @param [const int]port. Порт для отправк датаграмм
     */
    void balanceLoad(const Server& server, const char* buffer, int size, const int port);

private:
    /**
     * @brief IP адреса серверов для отправки датаграмм
     */
    const std::vector<std::string> destinationAddresses;
    /**
     * @brief Итератор для хранения текущего ip адреса
     */
    std::vector<std::string>::const_iterator currentIt;

};
