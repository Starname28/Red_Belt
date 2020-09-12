
// for_interview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

using namespace std;

void reverse(char* arr)
{
    if (!arr)
        return;
    
    char symb = NULL;
    size_t count = 0;
    
    do
    {
        symb = arr[count];
        ++count;

    } while (symb != '\0');

    --count;

    for (size_t i = 0; i < count / 2; ++i)
    {
        swap(arr[i], arr[count - i - 1]);
    }
}

int main()
{
    char arr[] = "123456789ygjxfyryxguhvojknivct7rse5Zzdxs5wr798900000087776";
    cout << arr << endl;
    reverse(arr);

    cout << arr << endl;
}
