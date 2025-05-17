#pragma once
#include <string>

// Класс для подготовки входного текста: очистка, замена J на I, разбиение на биграммы
class TextPreparation {
public:
    // Обрабатывает текст: удаляет не-буквы, приводит к верхнему регистру, добавляет X при необходимости
    static std::string prepareText(const std::string& text);
};