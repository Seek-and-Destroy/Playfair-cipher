#include "PlayfairCipher.h"

// Конструктор: подготавливает ключ и создаёт матрицу
PlayfairCipher::PlayfairCipher(const std::string& keyword) : key(keyword) {
    KeyPreparation::prepareKey(key); // Очищаем ключ
    matrix = KeyPreparation::createMatrix(key); // Создаём матрицу 5x5
}

// Функция шифрования: подготавливает текст и шифрует его
std::string PlayfairCipher::encrypt(const std::string& text) {
    std::string prepared = TextPreparation::prepareText(text); // Обрабатываем текст
    return Encryption::encrypt(prepared, matrix); // Шифруем
}

// Функция дешифрования: подготавливает текст и дешифрует его
std::string PlayfairCipher::decrypt(const std::string& text) {
    std::string prepared = TextPreparation::prepareText(text); // Обрабатываем текст
    return Decryption::decrypt(prepared, matrix); // Дешифруем
}