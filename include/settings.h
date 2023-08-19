#pragma once
#include <string>
#include <vector>

/**
 * @brief Структура для хранения параметров из конфигурационного файла
 */
struct Settings {
    /**
     * @brief IP адрес, на котором будет открыт сокет
     */
    std::string host_ip;
    /**
     * @brief Порт, на котором будет открыт сокет
     */
    int port = 0;
    /**
     * @brief Максимальное количество датаграмм в секунду, проходящее через балансировщик
     */
    int numberOfDatagrams = 0;
    /**
     * @brief IP адреса серверов, на которые необходимо перенаправлять датаграммы
     */
    std::vector<std::string> destinationAddresses;
};
