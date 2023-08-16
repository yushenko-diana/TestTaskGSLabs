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
     * @param [string]filename
     */
    SettingsParser(std::string filename);
    /**
     * @brief Деструктор
     */
    ~SettingsParser();
    /**
     * @brief Функция чтения параметров из конфигурационного файла
     * @param [Settings&]settings
     */
    void readParameters(Settings& settings);
private:
    /**
     * @brief Переменная для хранения конфигурационного файла
     */
    std::ifstream file;
};
