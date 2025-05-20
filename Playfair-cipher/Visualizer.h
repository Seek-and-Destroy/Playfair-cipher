#pragma once
#include <SFML/Graphics.hpp>
#include "Cipher.h"

// ����� ��� ������������ ���������� � �������������� SFML
class Visualizer {
public:
    // �����������: �������������� ���� � �����
    Visualizer();
    // ����������: ����������� ������ cipher;
    ~Visualizer();
    // ��������� �������� ���� ���������
    void run();

private:
    Cipher* cipher;

    sf::RenderWindow window; // ���� SFML

    sf::Font font; // ����� ��� ������

    std::string keyword, inputText, outputText, currentInput; // ������ ������������

    enum State { INPUT_KEYWORD, INPUT_TEXT, SELECT_MODE, SHOW_RESULT }; // ��������� ����������

    State state; // ������� ���������

    sf::Text displayText, promptText, resultText; // ��������� ������� ��� �����������

    // ������������ ������� (�������, ���� ������, �������� ����)
    void handleEvents();

    // ��������� ���������� ����
    void updateDisplay();
};
