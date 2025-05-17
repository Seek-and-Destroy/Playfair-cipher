#include "Visualizer.h"
#include <string>

// Конструктор: создаёт окно и настраивает текстовые элементы
Visualizer::Visualizer() : window(sf::VideoMode(800, 600), "Playfair Cipher"),
isEncryptMode(true), state(INPUT_KEYWORD) {
    // Загружаем шрифт Arial из системной папки Windows
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        window.close(); // Если шрифт не найден, закрываем окно
    }

    // Настраиваем текстовые элементы
    displayText.setFont(font);
    promptText.setFont(font);
    resultText.setFont(font);

    displayText.setCharacterSize(24); // Размер текста
    promptText.setCharacterSize(24);
    resultText.setCharacterSize(24);

    displayText.setFillColor(sf::Color::White); // Цвет текста
    promptText.setFillColor(sf::Color::White);
    resultText.setFillColor(sf::Color::White);
}

// Основной цикл программы: обрабатывает события и обновляет экран
void Visualizer::run() {
    while (window.isOpen()) {
        handleEvents(); // Обрабатываем ввод пользователя
        updateDisplay(); // Обновляем содержимое окна
    }
}

// Обработка событий: закрытие окна, ввод текста, нажатие клавиш
void Visualizer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Закрытие окна при нажатии на крестик
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Обработка ввода текста (только в состояниях ввода ключа или текста)
        if (event.type == sf::Event::TextEntered && state != SHOW_RESULT) {
            if (event.text.unicode < 128) { // Ограничиваемся ASCII символами
                char c = static_cast<char>(event.text.unicode);
                if (c == '\b' && !currentInput.empty()) {
                    // Backspace: удаляем последний символ
                    currentInput.pop_back();
                }
                else if (c == '\r' || c == '\n') {
                    // Enter: переходим к следующему состоянию
                    if (state == INPUT_KEYWORD) {
                        keyword = currentInput; // Сохраняем ключ
                        currentInput.clear();
                        state = INPUT_TEXT; // Переходим к вводу текста
                    }
                    else if (state == INPUT_TEXT) {
                        inputText = currentInput; // Сохраняем текст
                        currentInput.clear();
                        state = SELECT_MODE; // Переходим к выбору режима
                    }
                }
                else if (isalnum(c) || c == ' ') {
                    // Добавляем буквы, цифры или пробел
                    currentInput += c;
                }
            }
        }
        // Обработка нажатий клавиш
        if (event.type == sf::Event::KeyPressed) {
            if (state == SELECT_MODE) {
                // В режиме выбора: 1 — шифрование, 2 — дешифрование
                if (event.key.code == sf::Keyboard::Num1) {
                    isEncryptMode = true;
                    PlayfairCipher cipher(keyword);
                    outputText = cipher.encrypt(inputText); // Шифруем текст
                    state = SHOW_RESULT; // Показываем результат
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    isEncryptMode = false;
                    PlayfairCipher cipher(keyword);
                    outputText = cipher.decrypt(inputText); // Дешифруем текст
                    state = SHOW_RESULT; // Показываем результат
                }
            }
            else if (state == SHOW_RESULT && event.key.code == sf::Keyboard::Enter) {
                // В состоянии результата: Enter возвращает к вводу ключа
                state = INPUT_KEYWORD;
                currentInput.clear();
                keyword.clear();
                inputText.clear();
                outputText.clear();
            }
        }
    }
}

// Обновление окна: отображает текст и матрицу в зависимости от состояния
void Visualizer::updateDisplay() {
    window.clear(); // Очищаем окно (чёрный фон)

    // В зависимости от состояния отображаем разные подсказки и текст
    switch (state) {
    case INPUT_KEYWORD:
        promptText.setString("Enter keyword:"); // Подсказка для ввода ключа
        displayText.setString(currentInput);
        break;
    case INPUT_TEXT:
        promptText.setString("Enter text:"); // Подсказка для ввода текста
        displayText.setString(currentInput);
        break;
    case SELECT_MODE:
        promptText.setString("Press 1 to encrypt, 2 to decrypt"); // Подсказка для выбора режима
        displayText.setString("");
        break;
    case SHOW_RESULT:
        promptText.setString("Result (press Enter to restart):"); // Показываем результат
        displayText.setString(outputText);

        // Отображаем матрицу 5x5
        PlayfairCipher cipher(keyword);
        auto matrix = cipher.getMatrix();
        std::string matrixStr = "Matrix:\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matrixStr += matrix[i][j];
                matrixStr += " ";
            }
            matrixStr += "\n";
        }
        resultText.setString(matrixStr);
        resultText.setPosition(50, 300); // Позиция матрицы на экране
        window.draw(resultText);
        break;
    }

    // Устанавливаем позиции текста и отображаем
    promptText.setPosition(50, 50); // Подсказка вверху
    displayText.setPosition(50, 100); // Введённый текст ниже
    window.draw(promptText);
    window.draw(displayText);

    window.display(); // Обновляем экран
}