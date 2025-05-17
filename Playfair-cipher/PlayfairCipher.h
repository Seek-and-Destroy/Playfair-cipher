#pragma once
#include <string>
#include <vector>
#include "KeyPreparation.h"
#include "TextPreparation.h"
#include "Encryption.h"
#include "Decryption.h"

// Основной класс шифра Плейфера, объединяющий все операции
class PlayfairCipher {
private:
    std::string key; // Ключевое слово
    std::vector<std::vector<char>> matrix; // Матрица 5x5

public:
    // Конструктор: принимает ключевое слово и создаёт матрицу
    PlayfairCipher(const std::string& keyword);
    // Шифрует текст
    std::string encrypt(const std::string& text);
    // Дешифрует текст
    std::string decrypt(const std::string& text);
    // Возвращает матрицу для отображения
    std::vector<std::vector<char>> getMatrix() const { return matrix; }
};