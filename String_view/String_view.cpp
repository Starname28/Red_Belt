// String_view.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

vector<string_view> RetVec(string_view str)
{
    vector<string_view> ret;
    //string_view str = s;

    while (true)
    {
        size_t space = str.find(' ');

        ret.push_back(str.substr(0, space));

        if (space == str.npos)
            break;
        else
            str.remove_prefix(space + 1);
    }

    return ret;
}

int main()
{
    vector<string_view> vec(RetVec("Hello World!\n"));

    cout << vec[0] << endl;

    for (size_t i = 0; i < RetVec("Hello World!\n").size(); i++)
    {
        cout << RetVec("Hello World!\n")[i] << " " << "\n";
    }
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
