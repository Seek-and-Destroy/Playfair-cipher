#pragma once
#include <string>
#include <vector>

// Класс для дешифрования текста с использованием матрицы 5x5
class Decryption {
public:
    // Дешифрует текст, применяя правила Плейфера
    static std::string decrypt(const std::string& text, const std::vector<std::vector<char>>& matrix);
private:
    // Находит позицию буквы в матрице (строка и столбец)
    static void findPosition(char c, const std::vector<std::vector<char>>& matrix, int& row, int& col);
};