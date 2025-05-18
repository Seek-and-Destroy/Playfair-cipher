#pragma once
#include <SFML/Graphics.hpp>
#include "Cipher.h"

// Класс для графического интерфейса с использованием SFML
class Visualizer {
public:
    // Конструктор: инициализирует окно и шрифт
    Visualizer();
    // Запускает основной цикл программы
    void run();

private:
    sf::RenderWindow window; // Окно SFML

    sf::Font font; // Шрифт для текста

    std::string keyword, inputText, outputText, currentInput; // Данные пользователя

    bool isEncryptMode; // Режим: true — шифрование, false — дешифрование

    enum State { INPUT_KEYWORD, INPUT_TEXT, SELECT_MODE, SHOW_RESULT }; // Состояния интерфейса
    
    State state; // Текущее состояние
    
    sf::Text displayText, promptText, resultText; // Текстовые объекты для отображения

    // Обрабатывает события (клавиши, ввод текста, закрытие окна)
    void handleEvents();
    
    // Обновляет содержимое окна
    void updateDisplay();
};