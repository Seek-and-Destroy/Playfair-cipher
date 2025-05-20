#pragma once
#include <string>

class Cipher {
private:
    char** matrix;// Динамическая матрица 5x5

    std::string key; // Ключевое слово

    // Находит позицию буквы в матрице
    void findPosition(char c, int& row, int& col);

public:
    // Конструктор: создаёт матрицу из ключевого слова
    Cipher(const std::string& keyword);

    // Шифрует текст
    std::string encrypt(const std::string& text);

    // Дешифрует текст
    std::string decrypt(const std::string& text);

    // Возвращает матрицу для отображения
    char** getMatrix() const;

    ~Cipher();
};

// Отдельная функция для подготовки текста
std::string prepareText(const std::string& text);
