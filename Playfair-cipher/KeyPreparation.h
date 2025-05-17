#pragma once
#include <string>
#include <vector>

// Класс для подготовки ключа и создания матрицы 5x5 для шифра Плейфера
class KeyPreparation {
public:
    // Очищает ключ от повторов, приводит к верхнему регистру, заменяет J на I
    static void prepareKey(std::string& key);
    // Создает матрицу 5x5 из ключа и оставшихся букв алфавита
    static std::vector<std::vector<char>> createMatrix(const std::string& key);
};