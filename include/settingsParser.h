#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <settings.h>

/**
 * @brief Класс для парсинга конфигурационных параметров из файла конфигурации
 */
class SettingsParser {
public:
    /**
     * @brief Конструктор
     * @param [string]filename. Имя файла
     */
    SettingsParser(std::string filename);
    /**
     * @brief Деструктор
     */
    ~SettingsParser();
    /**
     * @brief Функция чтения параметров из конфигурационного файла
     * @param [Settings&]settings. Структура, хранящая конфигурационные параметры
     */
    void readParameters(Settings& settings);


private:
    /**
     * @brief Функция разделяющая строку по разделителю
     * @param [vector<string>&]array. Массив элементов
     * @param [string]str. Строка для разделения
     * @param [char]delimiter. Разделитель строки
     */
    void splitString(std::vector<std::string>& array, const std::string& str, const char delimiter);

    /**
     * @brief Функция, определяющая правильность скобочной последовательности
     * @param [string]str. Строка для проверки
     * @return Возвращает true, если последовательность верна, false, если не верна
     */
    bool isBracketSequenceRight(const std::string& str);

    /**
     * @brief Парсер массива
     * Функция принимает строку и из строки получает элементы, разделенные запятой
     * @param [string]str. Строка, содержащая массив
     */
    void parseArray(std::vector<std::string>& array, const std::string& str);

    /**
     * @brief Функция для проверки строки на соответствие IP адресу
     * @param [string]str. Строка для проверки
     * @return Возвращает true, если строка содержит IP адрес, false, если нет
    */
    bool isItIPAddress(const std::string& str);

    /**
     * @brief Функция для проверки корректности IP адреса, содержащегося в строке
     * @param [string]str. Строка для проверки
     * @return Возвращает true, если IP адрес корректен, false, если нет
    */
    bool isIPAddressCorrect(const std::string& str);

    /**
     * @brief Функция, проверяющая, является ли строка массивом
     * @param [string]str. Строка для проверки
     * @return Возвращает true, если строка содержит массив, false, если нет
     */
    bool isItArray(const std::string& str);
    /**
     * @brief Функция, проверяющая корректность IP адресов в массиве
     * @param [vector<string>&]array
     * @return Возвращает true, если адреса корректны, false, если нет
     */
    bool isIPAdressesCorrect(std::vector<std::string> array);
    /**
     * @brief Функция, проверяющая строку, содержащую число, на корректность
     * Функция проверяет строку на содержащую число на наличие в ней цифр
     * @param [string]str
     * @return Возвращает true, если число корректно, false, если нет
     */
    bool isNumberValid(const std::string str);

private:
    /**
     * @brief Переменная для хранения конфигурационного файла
     */
    std::ifstream file;
};
