#include "Decryption.h"

// Функция поиска позиции буквы в матрице 5x5
void Decryption::findPosition(char c, const std::vector<std::vector<char>>& matrix, int& row, int& col) {
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
    // Если буква не найдена, row и col остаются -1
}

// Функция дешифрования текста по правилам Плейфера
std::string Decryption::decrypt(const std::string& text, const std::vector<std::vector<char>>& matrix) {
    std::string result;

    // Обрабатываем текст по парам букв (биграммам)
    for (size_t i = 0; i < text.length(); i += 2) {
        int row1, col1, row2, col2;
        // Находим позиции двух букв текущей биграммы
        findPosition(text[i], matrix, row1, col1);
        findPosition(text[i + 1], matrix, row2, col2);

        // Правило 1: Если буквы в одной строке, берём предыдущие слева (циклически)
        if (row1 == row2) {
            result += matrix[row1][(col1 + 4) % 5]; // Предыдущая буква в строке
            result += matrix[row2][(col2 + 4) % 5];
        }
        // Правило 2: Если буквы в одном столбце, берём предыдущие сверху (циклически)
        else if (col1 == col2) {
            result += matrix[(row1 + 4) % 5][col1]; // Предыдущая буква в столбце
            result += matrix[(row2 + 4) % 5][col2];
        }
        // Правило 3: Если буквы в разных строках и столбцах, берём угловые буквы прямоугольника
        else {
            result += matrix[row1][col2]; // Буква на пересечении строки row1 и столбца col2
            result += matrix[row2][col1]; // Буква на пересечении строки row2 и столбца col1
        }
    }

    // Удаляем лишние X, добавленные при шифровании
    std::string cleaned;
    for (size_t i = 0; i < result.length(); i++) {
        cleaned += result[i];
        // Если X находится между одинаковыми буквами, пропускаем её
        if (i + 2 < result.length() && result[i + 1] == 'X' && result[i] == result[i + 2]) {
            i++;
        }
    }
    return cleaned;
}