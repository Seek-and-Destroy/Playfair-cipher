#include "Visualizer.h"
#include <string>

// �����������: ������ ���� � ����������� ��������� ��������
Visualizer::Visualizer() : cipher(nullptr), window(sf::VideoMode(800, 600), "Playfair Cipher"), state(INPUT_KEYWORD) {
    // ��������� ����� Arial �� ��������� ����� Windows
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        window.close(); // ���� ����� �� ������, ��������� ����
    }

    // ����������� ��������� ��������
    displayText.setFont(font);
    promptText.setFont(font);
    resultText.setFont(font);

    displayText.setCharacterSize(24); // ������ ������
    promptText.setCharacterSize(24);
    resultText.setCharacterSize(24);

    displayText.setFillColor(sf::Color::White); // ���� ������
    promptText.setFillColor(sf::Color::White);
    resultText.setFillColor(sf::Color::White);
}

// ����������
Visualizer::~Visualizer()  {
    if (cipher)
        delete cipher;
}

// �������� ���� ���������: ������������ ������� � ��������� �����
void Visualizer::run() {
    while (window.isOpen()) {
        handleEvents(); // ������������ ���� ������������
        updateDisplay(); // ��������� ���������� ����
    }
}

// ��������� �������: �������� ����, ���� ������, ������� ������
void Visualizer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // �������� ���� ��� ������� �� �������
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if ((state == INPUT_KEYWORD) && (cipher != nullptr)) // ������� ���� ����� ����. �����, ���� ��� ��� ����
            state = INPUT_TEXT;

        // ��������� ����� ������ (������ � ���������� ����� ����� ��� ������)
        if (event.type == sf::Event::TextEntered && state != SHOW_RESULT) {
            if (event.text.unicode < 128) { // �������������� ASCII ���������
                char c = static_cast<char>(event.text.unicode);
                if (c == '\b' && !currentInput.empty()) {
                    // Backspace: ������� ��������� ������
                    currentInput.pop_back();
                }
                else if ((c == '\r' || c == '\n') && currentInput != "") {
                    // Enter: ��������� � ���������� ���������
                    if (state == INPUT_KEYWORD) {
                        cipher = new Cipher(currentInput); // ��������� �������
                        currentInput.clear();
                        state = INPUT_TEXT; // ��������� � ����� ������
                    }
                    else if (state == INPUT_TEXT) {
                        inputText = currentInput; // ��������� �����
                        currentInput.clear();
                        state = SELECT_MODE; // ��������� � ������ ������
                    }
                }
                else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
                    // ��������� ����� ��� ������
                    currentInput += c;
                }
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (state == SELECT_MODE) {
                // � ������ ������: 1 � ����������, 2 � ������������
                if (event.key.code == sf::Keyboard::Num1) {
                    outputText = cipher->encrypt(inputText); // �������
                    state = SHOW_RESULT; // ���������� ���������
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    outputText = cipher->decrypt(inputText); // ���������
                    state = SHOW_RESULT; // ���������� ���������
                }
            }
            else if (state == SHOW_RESULT && event.key.code == sf::Keyboard::Enter) {
                // � ��������� ����������: Enter ���������� � ����� �����
                state = INPUT_KEYWORD;
                currentInput.clear();
                keyword.clear();
                inputText.clear();
                outputText.clear();
            }
        }
    }
}

// ���������� ����: ���������� ����� � ������� � ����������� �� ���������
void Visualizer::updateDisplay() {
    window.clear(); // ������� ���� (������ ���)

    // � ����������� �� ��������� ���������� ������ ��������� � �����
    switch (state) {
    case INPUT_KEYWORD:
        promptText.setString("Enter keyword:"); // ��������� ��� ����� �����
        displayText.setString(currentInput);
        break;
    case INPUT_TEXT:
        promptText.setString("Enter text:"); // ��������� ��� ����� ������
        displayText.setString(currentInput);
        break;
    case SELECT_MODE:
        promptText.setString("Press 1 to encrypt, 2 to decrypt"); // ��������� ��� ������ ������
        displayText.setString("");
        break;
    case SHOW_RESULT:
        promptText.setString("Result (press Enter to restart):"); // ���������� ���������
        displayText.setString(outputText);

        // ���������� ������� 5x5
        char** matrix = cipher->getMatrix(); // �������� �������
        std::string matrixStr = "Matrix:\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matrixStr += matrix[i][j];
                matrixStr += " "; // ������ ����� �������
            }
            matrixStr += "\n"; // ����� ������
        }

        resultText.setString(matrixStr);
        resultText.setPosition(50, 300); // ������� ������� �� ������
        window.draw(resultText);
        break;
    }

    // ������������� ������� ������ � ����������
    promptText.setPosition(50, 50); // ��������� ������
    displayText.setPosition(50, 100); // �������� ����� ����
    window.draw(promptText);
    window.draw(displayText);
    window.display(); // ��������� �����
}
