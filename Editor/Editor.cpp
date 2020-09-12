// Editor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Editor {
public:
    Editor()
    {
        cursor = text.begin();
    }
    void Left()
    {
        if (cursor != text.begin())
            cursor = prev(cursor);
    }// �������� ������ �����
    void Right()
    {
        if (cursor != text.end())
            cursor = next(cursor);
    }// �������� ������ ������
    void Insert(char token)
    {
        text.insert(cursor, token);
    }// �������� ������ token
    void Copy(size_t tokens)
    {
        const auto iter = ComputeCursor(tokens);
        inserter(iter);
    }// c����������
                               // �� ����� tokens ��������,
                               // ������� � ������� ������� �������
    void Cut(size_t tokens)
    {
        const auto iter = ComputeCursor(tokens);
        inserter(iter);
        deleter(iter);
    }// �������� �� ����� tokens ��������,
                              // ������� � ������� ������� �������
    void Paste()
    {
        if (!buffer.empty())
            text.insert(cursor, buffer.begin(), buffer.end());
    }// �������� ���������� ������
                   // � ������� ������� �������
    string GetText() const
    {
        return string(text.begin(),text.end());
    }// �������� ������� ����������
                             // ���������� ���������
private:
    std::list<char> text;
    std::list<char> buffer;
    std::list<char>::iterator cursor;

    void deleter(const list<char>::iterator& it)
    {
        text.erase(it, cursor);
    }

    void inserter(const list<char>::iterator& it)
    {
        buffer.clear();
        buffer.insert(buffer.end(), it, cursor);
    }
    std::list<char>::iterator ComputeCursor(size_t tokens)
    {
        const size_t dist_to_end = std::distance(cursor, text.end());
        const auto tmp_iter = cursor;
        tokens >= dist_to_end ? cursor = text.end() : cursor = std::next(cursor, tokens);

        return tmp_iter;
    }
};
int main() {
    Editor editor;
    const string text = "hello, world";
    for (char c : text) {
        editor.Insert(c);
    }
    // ������� ��������� ���������: `hello, world|`
    for (size_t i = 0; i < text.size(); ++i) {
        editor.Left();
    }
    // ������� ��������� ���������: `|hello, world`
    editor.Cut(7);
    // ������� ��������� ���������: `|world`
    // � ������ ������ ��������� ����� `hello, `
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
    }
    // ������� ��������� ���������: `world|`
    editor.Insert(',');
    editor.Insert(' ');
    // ������� ��������� ���������: `world, |`
    editor.Paste();
    // ������� ��������� ���������: `world, hello, |`
    editor.Left();
    editor.Left();
    //������� ��������� ���������: `world, hello|, `
    editor.Cut(3); // ����� �������� 2 �������
    // ������� ��������� ���������: `world, hello|`
    cout << editor.GetText();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
