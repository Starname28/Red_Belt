// NewLang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "profile.h"
#include "Learner.cpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;
//
//class Learner {
//private:
//    set<string> dict;
//
//public:
//    int Learn(const vector<string>& words) {
//        int newWords = 0;
//        {
//            LOG_DURATION("learn Circle");
//            for (const auto& word : words) {
//                LOG_DURATION("Interation");
//                if (!count(dict.begin(), dict.end(), word)) {
//                    LOG_DURATION("IF Interation");
//                    ++newWords;
//                    dict.insert(word);
//                }
//            }}
//        return newWords;
//    }
//
//    vector<string> KnownWords()
//    {
//        vector<string> vec(dict.begin(), dict.end());
//        return vec;
//    }
//};

int main() {
    Learner learner;
    string line;
    bool r = true;
    int count = 0;
    while (count !=3) {
        getline(cin, line);
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }

        cout << learner.Learn(words) << "\n";
        count++;
    }
    cout << "=== known words ===\n";
    {
        LOG_DURATION("learn");
        for (auto word : learner.KnownWords()) {
            cout << word << "\n";
        }
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
