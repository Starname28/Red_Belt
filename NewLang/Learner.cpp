#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "profile.h"

using namespace std;

class Learner {
private:
    set<string> s;
public:
    int Learn(const vector<string>& words) {
        int prevSize = s.size();
        for (const auto& word : words)
            s.insert(word);
        return s.size() - prevSize;
    }

    vector<string> KnownWords() {
        return {s.begin(), s.end()};
    }
};