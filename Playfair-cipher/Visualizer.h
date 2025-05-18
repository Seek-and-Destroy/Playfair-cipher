#pragma once
#include <SFML/Graphics.hpp>
#include "Cipher.h"

// ����� ��� ������������ ���������� � �������������� SFML
class Visualizer {
public:
    // �����������: �������������� ���� � �����
    Visualizer();
    // ��������� �������� ���� ���������
    void run();

private:
    sf::RenderWindow window; // ���� SFML

    sf::Font font; // ����� ��� ������

    std::string keyword, inputText, outputText, currentInput; // ������ ������������

    bool isEncryptMode; // �����: true � ����������, false � ������������

    enum State { INPUT_KEYWORD, INPUT_TEXT, SELECT_MODE, SHOW_RESULT }; // ��������� ����������
    
    State state; // ������� ���������
    
    sf::Text displayText, promptText, resultText; // ��������� ������� ��� �����������

    // ������������ ������� (�������, ���� ������, �������� ����)
    void handleEvents();
    
    // ��������� ���������� ����
    void updateDisplay();
};