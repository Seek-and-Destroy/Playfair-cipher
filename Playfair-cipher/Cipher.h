#pragma once
#include <string>

class Cipher {
private:
    char** matrix;// ������������ ������� 5x5

    std::string key; // �������� �����

    // ������� ������� ����� � �������
    void findPosition(char c, int& row, int& col);

public:
    // �����������: ������ ������� �� ��������� �����
    Cipher(const std::string& keyword);

    // ������� �����
    std::string encrypt(const std::string& text);

    // ��������� �����
    std::string decrypt(const std::string& text);

    // ���������� ������� ��� �����������
    char** getMatrix() const;

    ~Cipher();
};

// ��������� ������� ��� ���������� ������
std::string prepareText(const std::string& text);
