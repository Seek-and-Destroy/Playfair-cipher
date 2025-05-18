#include "Cipher.h"
#include <cctype>

// ���������� ������: �������� ��-����, ������ J �� I, ��������� �� ��������
std::string prepareText(const std::string& text) {
    // ������� �����: ������ �����, ������� �������, J->I
    std::string result;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A'; // ����������� � ������� �������
            }
            if (c == 'J') {
                c = 'I'; // �������� J �� I
            }
            result += c;
        }
    }

    // ��������� �� ��������, �������� X ��� �������������
    std::string prepared;
    for (int i = 0; i < result.length(); i++) {
        prepared += result[i]; // ��������� ������� �����
        if (i + 1 < result.length() && result[i] == result[i + 1]) {
            // ���� ���������� ����� ������, ��������� X
            prepared += 'X';
        }
        else if (i + 1 < result.length()) {
            // ��������� ��������� ����� � ���������� ��������
            prepared += result[i + 1];
            i++;
        }
        else {
            // ��� �������� ����� ��������� X
            prepared += 'X';
        }
    }
    return prepared;
}

// �����������: ������ ������� 5x5 �� ������ ��������� �����
Cipher::Cipher(const std::string& keyword) {
    key = keyword; // ��������� �������� �����

    // ������� ����: ������� �������, J->I, ������� �������
    std::string temp = key;
    key = "";
    for (int i = 0; i < temp.length(); i++) {
        char c = temp[i];
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A'; // ����������� � ������� �������
        }
        if (c == 'J') {
            c = 'I'; // �������� J �� I
        }
        temp[i] = c;
    }
    for (int i = 0; i < temp.length(); i++) {
        bool alreadyUsed = false;
        for (int j = 0; j < key.length(); j++) {
            if (key[j] == temp[i]) {
                alreadyUsed = true;
                break;
            }
        }
        if (!alreadyUsed) {
            key += temp[i];
        }
    }

    // �������������� ������� ���������
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = ' ';
        }
    }

    // ��������� ������� ������
    int row = 0, col = 0;
    for (int i = 0; i < key.length(); i++) {
        matrix[row][col] = key[i];
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }

    // ��������� ���������� ������ ������� �������� (����� J)
    std::string used = key;
    char letter = 'A';
    while (row < 5) {
        if (letter == 'J') {
            letter++;
        }
        bool isUsed = false;
        for (int i = 0; i < used.length(); i++) {
            if (used[i] == letter) {
                isUsed = true;
                break;
            }
        }
        if (!isUsed) {
            matrix[row][col] = letter;
            used += letter;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
        letter++;
    }
}

// ����������: matrix � ����������� ������, ������� �� ���������
Cipher::~Cipher() {
    // matrix ������������� ���������, ��� ��� ��� ����������� ������
    // key (std::string) ����� ��������� �������������
}

// ����� ������� ����� � �������
void Cipher::findPosition(char c, int& row, int& col) {
    row = -1;
    col = -1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i; // ���������� ������
                col = j; // ���������� �������
                return;
            }
        }
    }
}

// ���������� ������ �� �������� ��������
std::string Cipher::encrypt(const std::string& text) {
    std::string prepared = prepareText(text); // �������������� �����
    std::string result;

    // ������������ ���� ���� (��������)
    for (int i = 0; i < prepared.length(); i += 2) {
        int row1, col1, row2, col2;
        findPosition(prepared[i], row1, col1); // ������� ������� ������ �����
        findPosition(prepared[i + 1], row2, col2); // ������� ������� ������ �����

        // ������� 1: ���� ����� � ����� ������, ���� ��������� ������
        if (row1 == row2) {
            result += matrix[row1][(col1 + 1) % 5];
            result += matrix[row2][(col2 + 1) % 5];
        }
        // ������� 2: ���� ����� � ����� �������, ���� ��������� �����
        else if (col1 == col2) {
            result += matrix[(row1 + 1) % 5][col1];
            result += matrix[(row2 + 1) % 5][col2];
        }
        // ������� 3: ���� ����� � ������ ������� � ��������, ���� ���� ��������������
        else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }
    return result;
}

// ������������ ������ �� �������� ��������
std::string Cipher::decrypt(const std::string& text) {
    std::string prepared = prepareText(text); // �������������� �����
    std::string result;

    // ������������ ���� ���� (��������)
    for (int i = 0; i < prepared.length(); i += 2) {
        int row1, col1, row2, col2;
        findPosition(prepared[i], row1, col1); // ������� ������� ������ �����
        findPosition(prepared[i + 1], row2, col2); // ������� ������� ������ �����

        // ������� 1: ���� ����� � ����� ������, ���� ���������� �����
        if (row1 == row2) {
            result += matrix[row1][(col1 + 4) % 5]; // ����� ����� (4 = 5-1)
            result += matrix[row2][(col2 + 4) % 5];
        }
        // ������� 2: ���� ����� � ����� �������, ���� ���������� ������
        else if (col1 == col2) {
            result += matrix[(row1 + 4) % 5][col1]; // ����� ����� (4 = 5-1)
            result += matrix[(row2 + 4) % 5][col2];
        }
        // ������� 3: ���� ����� � ������ ������� � ��������, ���� ���� ��������������
        else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }
    }

    // ������� ������ X, ����������� ��� ����������
    std::string cleaned;
    for (int i = 0; i < result.length(); i++) {
        cleaned += result[i];
        // ���� X ����� ����������� �������, ���������� ���
        if (i + 2 < result.length() && result[i + 1] == 'X' && result[i] == result[i + 2]) {
            i++;
        }
    }
    return cleaned;
}

// ���������� ������� ��� ������������ ������ (���������� ��� ������ ���������� ������)
char** Cipher::getMatrix() const {
    // �������� ������ ��� ������� ���������� (5 �����)
    char** result = new char* [5];
    // ��� ������ ������ �������� ������ � �������� ������
    for (int i = 0; i < 5; i++) {
        result[i] = new char[5]; // �������� ������ ��� 5 ��������
        for (int j = 0; j < 5; j++) {
            result[i][j] = matrix[i][j]; // �������� ������ �� matrix
        }
    }
    return result;
}