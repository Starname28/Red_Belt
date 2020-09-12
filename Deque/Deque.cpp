// Deque.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Deque
{
public:

    Deque() : m_sSizeDeque(0)
    {}

    bool Empty() const
    {
        if (m_vtPushFront.empty() && m_vtPushBack.empty())
        {
            return true;
        }
        return false;
    }

    size_t Size() const
    {
        return m_sSizeDeque;
    }

    T& operator[](size_t index)
    {
        if (index < m_vtPushFront.size())
        {
            return m_vtPushFront[m_vtPushFront.size() - 1 - index];
        }
        else
        {
            return m_vtPushBack[index - m_vtPushFront.size()];
        }
    }

    const T& operator[](size_t index) const
    {
        if (index < m_vtPushFront.size())
        {
            return m_vtPushFront[m_vtPushFront.size() - 1 - index];
        }
        else
        {
            return m_vtPushBack[index - m_vtPushFront.size()];
        }
    }

    T& At(size_t index)
    {
        if (index >= 0 && index < m_sSizeDeque)
        {
            if (index < m_vtPushFront.size())
            {
                return m_vtPushFront[m_vtPushFront.size() - 1 - index];
            }
            else
            {
                return m_vtPushBack[index - m_vtPushFront.size()];
            }
        }

        throw out_of_range("Out of range");
    }

    const T& At(size_t index) const
    {
        if (index >= 0 && index < m_sSizeDeque)
        {
            if (index < m_vtPushFront.size())
            {
                return m_vtPushFront[m_vtPushFront.size() - 1 - index];
            }
            else
            {
                return m_vtPushBack[index - m_vtPushFront.size()];
            }
        }
            
        throw out_of_range("Out of range");
       
    }

    const T& Front() const
    {
        if (!m_vtPushFront.empty())
            return m_vtPushFront.back();
        else
            return m_vtPushBack.front();
    }

    T& Front()
    {
        if (!m_vtPushFront.empty())
            return m_vtPushFront.back();
        else
            return m_vtPushBack.front();
    }

    const T& Back() const
    {
        if (!m_vtPushBack.empty())
            return m_vtPushBack.back();
        else
            return m_vtPushFront.front();
    }

    T& Back()
    {
        if (!m_vtPushBack.empty())
            return m_vtPushBack.back();
        else
            return m_vtPushFront.front();
    }

    void PushBack(T element)
    {
        m_sSizeDeque++;
        m_vtPushBack.emplace_back(element);
    }

    void PushFront(T element)
    {
        m_sSizeDeque++;
        m_vtPushFront.emplace_back(element);
     //  m_vtPushFront.emplace(m_vtPushFront.begin(), element);
    }

private:
    vector<T> m_vtPushFront;
    vector<T> m_vtPushBack;
    size_t    m_sSizeDeque;
  //  vector<T> ret;
};

int main()
{
    /*Deque<int> deq;
    deq.PushFront(1);
    deq.PushFront(2);
    cout << deq.Front() << endl;*/
    return 0;
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
