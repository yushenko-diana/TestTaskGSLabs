#pragma once
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
/**
 * @brief Класс, описывающий сервер
 */
class Server {
public:
    /**
    * @brief Конструктор класса сервера
    * @param [string]ipAddress IP адрес, на котором будет открыт сокет
    * @param [int]port. Порт, на котором будет открыт сокет
    */
    Server(const std::string ipAddress, int port);
    /**
     * @brief Деструктор класса сервера
     */
    ~Server();
    /**
     * @brief Функция отправки датаграммы
     * @param [const char*]buffer. Датаграмма
     * @param [int]datagramSize
     * @param [bool]blockWrite. По умолчанию параметр имеет значение false
     * @param [string]ipAddr. По умолчанию параметр имеет значение ""
     * @param [int]port. По умолчанию параметр имеет значение 0
     * @return Возвращает количество отправленных байт
     */
    int write(const char* buffer, int datagramSize, bool blockWrite = false, std::string ipAddr = "", int port = 0) const;
    /**
     * @brief Функция чтения датаграмм
     * @param [char*]buffer
     * @param [bool]blockRead. По умолчанию параметр false
     * @return Возвращает количество считанных байт
     */
    int read(char* buffer, bool blockRead = false);

private:
    /**
     * @brief Структура, хранящая адрес отправки
     */
    struct sockaddr_in senderAddr;
    /**
     * @brief Параметр, хранящий сокет сервера
     */
    int serverSocket;
};
