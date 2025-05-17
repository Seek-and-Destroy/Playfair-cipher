#include "KeyPreparation.h"
#include <algorithm>

// Функция подготовки ключа: приводит к верхнему регистру, заменяет J на I, убирает повторы
void KeyPreparation::prepareKey(std::string& key) {
    // Приводим все буквы к верхнему регистру и заменяем J на I
    for (char& c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // J не используется в шифре Плейфера, заменяем на I
    }

    // Удаляем повторяющиеся буквы, сохраняя порядок
    std::string uniqueKey;
    for (char c : key) {
        if (uniqueKey.find(c) == std::string::npos) { // Если буквы еще нет в uniqueKey
            uniqueKey += c;
        }
    }
    key = uniqueKey; // Заменяем исходный ключ на очищенный
}

// Функция создания матрицы 5x5: заполняет ключом, затем добавляет оставшиеся буквы алфавита
std::vector<std::vector<char>> KeyPreparation::createMatrix(const std::string& key) {
    // Создаем двумерный вектор 5x5, изначально заполненный пробелами
    std::vector<std::vector<char>> matrix(5, std::vector<char>(5, ' '));
    std::string used = key; // Сохраняем использованные буквы из ключа

    // Заполняем матрицу буквами ключа
    int row = 0, col = 0;
    for (char c : key) {
        matrix[row][col] = c; // Добавляем букву в текущую позицию
        col++;
        if (col == 5) { // Если строка заполнена, переходим на следующую
            col = 0;
            row++;
        }
    }

    // Заполняем оставшиеся ячейки буквами алфавита (кроме J)
    char letter = 'A';
    while (row < 5) {
        if (letter == 'J') letter++; // Пропускаем J, так как она заменяется на I
        if (used.find(letter) == std::string::npos) { // Если буква еще не использована
            matrix[row][col] = letter;
            col++;
            if (col == 5) { // Переход на следующую строку
                col = 0;
                row++;
            }
        }
        letter++;
    }
    return matrix;
}