#include "Cipher.h"
#include <cctype>


// Подготовка текста: удаление не-букв, замена J на I, разбиение на биграммы
std::string prepareText(const std::string& text) {
    // Очищаем текст: только буквы, верхний регистр, J->I
    std::string result;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A'; // Преобразуем в верхний регистр
            }
            if (c == 'J') {
                c = 'I'; // Заменяем J на I
            }
            result += c;
        }
    }

    // Разбиваем на биграммы, добавляя X при необходимости
    std::string prepared;
    for (int i = 0; i < result.length(); i++) {
        prepared += result[i]; // Добавляем текущую букву
        if (i + 1 < result.length() && result[i] == result[i + 1]) {
            // Если одинаковые буквы подряд, вставляем X
            prepared += 'X';
        }
        else if (i + 1 < result.length()) {
            // Добавляем следующую букву и пропускаем итерацию
            prepared += result[i + 1];
            i++;
        }
        else {
            // Для нечётной длины добавляем X
            prepared += 'X';
        }
    }
    return prepared;
}

// Конструктор: создаёт матрицу 5x5 на основе ключевого слова
Cipher::Cipher(const std::string& keyword) {
    key = keyword; // Сохраняем ключевое слово

    // Очищаем ключ: верхний регистр, J->I, убираем повторы
    std::string temp = key;
    key = "";
    for (int i = 0; i < temp.length(); i++) {
        char c = temp[i];
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A'; // Преобразуем в верхний регистр
        }
        if (c == 'J') {
            c = 'I'; // Заменяем J на I
        }
        temp[i] = c;
    }
    for (int i = 0; i < temp.length(); i++) {
        bool alreadyUsed = false;
        for (int j = 0; j < key.length(); j++) {
            if (key[j] == temp[i]) {
                alreadyUsed = true;
                break;
            }
        }
        if (!alreadyUsed) {
            key += temp[i];
        }
    }

    // Выделяем память под матрицу
    matrix = new char*[5];
    for (int i = 0; i < 5; i++) {
        matrix[i] = new char[5];
    }

    // Заполняем матрицу ключом
    int row = 0, col = 0;
    for (int i = 0; i < key.length(); i++) {
        matrix[row][col] = key[i];
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }

    // Заполняем оставшиеся ячейки буквами алфавита (кроме J)
    std::string used = key;
    char letter = 'A';
    while (row < 5) {
        if (letter == 'J') {
            letter++;
        }
        bool isUsed = false;
        for (int i = 0; i < used.length(); i++) {
            if (used[i] == letter) {
                isUsed = true;
                break;
            }
        }
        if (!isUsed) {
            matrix[row][col] = letter;
            used += letter;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
        letter++;
    }
}

// Деструктор: очистка памяти массива
Cipher::~Cipher() {
    for (int i = 0; i < 5; i++) {
        delete matrix[i];
    }
    delete matrix;
}

void Cipher::findPosition(char c, int& row, int& col) {
    if (c == 'J') c = 'I';
    for (int r = 0; r < 5; ++r) {
        for (int c2 = 0; c2 < 5; ++c2) {
            if (matrix[r][c2] == c) {
                row = r;
                col = c2;
                return;
            }
        }
    }
}

std::string Cipher::encrypt(const std::string& text) {
    std::string prepared = prepareText(text);
    std::string result = "";

    for (size_t i = 0; i < prepared.length(); i += 2) {
        char a = prepared[i];
        char b = prepared[i + 1];
        int row1, col1, row2, col2;

        findPosition(a, row1, col1);
        findPosition(b, row2, col2);

        if (row1 == row2) {
            result += matrix[row1][(col1 + 1) % 5];
            result += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            result += matrix[(row1 + 1) % 5][col1];
            result += matrix[(row2 + 1) % 5][col2];
        } else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }

    return result;
}

std::string Cipher::decrypt(const std::string& text) {
    std::string prepared = prepareText(text);
    std::string result = "";

    for (size_t i = 0; i < prepared.length(); i += 2) {
        char a = prepared[i];
        char b = prepared[i + 1];
        int row1, col1, row2, col2;

        findPosition(a, row1, col1);
        findPosition(b, row2, col2);

        if (row1 == row2) {
            result += matrix[row1][(col1 + 4) % 5];
            result += matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            result += matrix[(row1 + 4) % 5][col1];
            result += matrix[(row2 + 4) % 5][col2];
        } else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }

    return result;
}


// Возвращает матрицу как динамический массив (вызывающий код должен освободить память)
char** Cipher::getMatrix() const {
    return matrix;
}
