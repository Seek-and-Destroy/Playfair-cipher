#include "TextPreparation.h"
#include <cctype>

// Функция подготовки текста: очищает, заменяет J на I, разбивает на биграммы
std::string TextPreparation::prepareText(const std::string& text) {
    // Удаляем все не-буквы, приводим к верхнему регистру, заменяем J на I
    std::string result;
    for (char c : text) {
        if (isalpha(c)) { // Проверяем, что символ — буква
            c = toupper(c);
            if (c == 'J') c = 'I'; // Заменяем J на I
            result += c;
        }
    }

    // Разбиваем текст на пары букв (биграммы), добавляя X при необходимости
    std::string prepared;
    for (size_t i = 0; i < result.length(); i++) {
        prepared += result[i]; // Добавляем текущую букву
        if (i + 1 < result.length() && result[i] == result[i + 1]) {
            // Если две одинаковые буквы подряд, вставляем X между ними
            prepared += 'X';
        }
        else if (i + 1 < result.length()) {
            // Если есть следующая буква, добавляем её и пропускаем итерацию
            prepared += result[++i];
        }
        else {
            // Если текст нечетной длины, добавляем X в конец
            prepared += 'X';
        }
    }
    return prepared;
}