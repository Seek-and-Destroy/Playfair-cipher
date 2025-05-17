#include "Encryption.h"

// Функция поиска позиции буквы в матрице 5x5
void Encryption::findPosition(char c, const std::vector<std::vector<char>>& matrix, int& row, int& col) {
    row = -1;
    col = -1;
    // Перебираем все ячейки матрицы
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i; // Сохраняем строку
                col = j; // Сохраняем столбец
                return;
            }
        }
    }
    // Если буква не найдена, row и col остаются -1 (это ошибка, но обрабатывается внешним кодом)
}

// Функция шифрования текста по правилам Плейфера
std::string Encryption::encrypt(const std::string& text, const std::vector<std::vector<char>>& matrix) {
    std::string result;

    // Обрабатываем текст по парам букв (биграммам)
    for (size_t i = 0; i < text.length(); i += 2) {
        int row1, col1, row2, col2;
        // Находим позиции двух букв текущей биграммы
        findPosition(text[i], matrix, row1, col1);
        findPosition(text[i + 1], matrix, row2, col2);

        // Правило 1: Если буквы в одной строке, берём следующие справа (циклически)
        if (row1 == row2) {
            result += matrix[row1][(col1 + 1) % 5]; //  // Следующая буква в строке
            result += matrix[row2][(col2 + 1) % 5];
        }
        // Правило 2: Если буквы в одном столбце, берём следующие снизу (циклически)
        else if (col1 == col2) {
            result += matrix[(row1 + 1) % 5][col1]; // Следующая буква в столбце
            result += matrix[(row2 + 1) % 5][col2];
        }
        // Правило 3: Если буквы в разных строках и столбцах, берём угловые буквы прямоугольника
        else {
            result += matrix[row1][col2]; // Буква на пересечении строки row1 и столбца col2
            result += matrix[row2][col1]; // Буква на пересечении строки row2 и столбца col1
        }
    }
    return result;
}