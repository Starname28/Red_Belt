// Thread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <future>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int ret(const vector<int>& first,
    const vector<int>& second)
{
    future<int> f = async([&first]
        {
            return accumulate(first.begin(), first.end(), 0);
        });
    int s = accumulate(second.begin(), second.end(), 0);
    return f.get() + s;
}

int main()
{
    std::cout << ret({ 123,4,6,7 }, { 12,7,8 }) << endl;
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
