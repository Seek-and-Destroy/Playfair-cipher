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

    // Инициализируем матрицу пробелами
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = ' ';
        }
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

// Деструктор: matrix — статический массив, очистка не требуется
Cipher::~Cipher() {
    // matrix автоматически очищается, так как это статический массив
    // key (std::string) также очищается автоматически
}

// Поиск позиции буквы в матрице
void Cipher::findPosition(char c, int& row, int& col) {
    row = -1;
    col = -1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i; // Запоминаем строку
                col = j; // Запоминаем столбец
                return;
            }
        }
    }
}

// Шифрование текста по правилам Плейфера
std::string Cipher::encrypt(const std::string& text) {
    std::string prepared = prepareText(text); // Подготавливаем текст
    std::string result;

    // Обрабатываем пары букв (биграммы)
    for (int i = 0; i < prepared.length(); i += 2) {
        int row1, col1, row2, col2;
        findPosition(prepared[i], row1, col1); // Находим позицию первой буквы
        findPosition(prepared[i + 1], row2, col2); // Находим позицию второй буквы

        // Правило 1: Если буквы в одной строке, берём следующие справа
        if (row1 == row2) {
            result += matrix[row1][(col1 + 1) % 5];
            result += matrix[row2][(col2 + 1) % 5];
        }
        // Правило 2: Если буквы в одном столбце, берём следующие снизу
        else if (col1 == col2) {
            result += matrix[(row1 + 1) % 5][col1];
            result += matrix[(row2 + 1) % 5][col2];
        }
        // Правило 3: Если буквы в разных строках и столбцах, берём углы прямоугольника
        else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }
    return result;
}

// Дешифрование текста по правилам Плейфера
std::string Cipher::decrypt(const std::string& text) {
    std::string prepared = prepareText(text); // Подготавливаем текст
    std::string result;

    // Обрабатываем пары букв (биграммы)
    for (int i = 0; i < prepared.length(); i += 2) {
        int row1, col1, row2, col2;
        findPosition(prepared[i], row1, col1); // Находим позицию первой буквы
        findPosition(prepared[i + 1], row2, col2); // Находим позицию второй буквы

        // Правило 1: Если буквы в одной строке, берём предыдущие слева
        if (row1 == row2) {
            result += matrix[row1][(col1 + 4) % 5]; // Сдвиг влево (4 = 5-1)
            result += matrix[row2][(col2 + 4) % 5];
        }
        // Правило 2: Если буквы в одном столбце, берём предыдущие сверху
        else if (col1 == col2) {
            result += matrix[(row1 + 4) % 5][col1]; // Сдвиг вверх (4 = 5-1)
            result += matrix[(row2 + 4) % 5][col2];
        }
        // Правило 3: Если буквы в разных строках и столбцах, берём углы прямоугольника
        else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }

    // Удаляем лишние X, добавленные при шифровании
    std::string cleaned;
    for (int i = 0; i < result.length(); i++) {
        cleaned += result[i];
        // Если X между одинаковыми буквами, пропускаем его
        if (i + 2 < result.length() && result[i + 1] == 'X' && result[i] == result[i + 2]) {
            i++;
        }
    }
    return cleaned;
}

// Возвращает матрицу как динамический массив (вызывающий код должен освободить память)
char** Cipher::getMatrix() const {
    // Выделяем память для массива указателей (5 строк)
    char** result = new char* [5];
    // Для каждой строки выделяем память и копируем данные
    for (int i = 0; i < 5; i++) {
        result[i] = new char[5]; // Выделяем память для 5 символов
        for (int j = 0; j < 5; j++) {
            result[i][j] = matrix[i][j]; // Копируем символ из matrix
        }
    }
    return result;
}