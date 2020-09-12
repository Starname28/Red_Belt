// Bad_Macro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\Sort_By_Macro\test_runner.h"
#include <algorithm>
#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

template<typename Iterator>
class IterRange
{
    Iterator first, last;
public:
    IterRange(Iterator first, Iterator second)
        : first(first), last(second)
    {}


    Iterator begin()const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }
};

template <typename T>
 auto Head(T& vec, size_t s)//IterRange<typename vector<T>::iterator>
{
    return IterRange( vec.begin(), next(vec.begin(), min(s, vec.size())));
}

template <typename Iter>
IterRange<Iter> MakeRange(Iter begin, Iter end)
{
    return IterRange{begin, end};
}

int main() {
   const  vector<int> vec = { 1,2,3,4,5,7,8,6 };

    for (const auto& ch : Head(vec, 5))
    {
        cout << ch << ' ';
    }

    auto middle = MakeRange(vec.begin() + 3, vec.end());
    cout << endl;
    for (const auto& ch : middle)
    {
        cout << ch << ' ';
    }
    return 0;
}