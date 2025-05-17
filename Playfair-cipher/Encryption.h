#pragma once
#include <string>
#include <vector>

// Класс для шифрования текста с использованием матрицы 5x5
class Encryption {
public:
    // Шифрует текст, применяя правила Плейфера
    static std::string encrypt(const std::string& text, const std::vector<std::vector<char>>& matrix);
private:
    // Находит позицию буквы в матрице (строка и столбец)
    static void findPosition(char c, const std::vector<std::vector<char>>& matrix, int& row, int& col);
};