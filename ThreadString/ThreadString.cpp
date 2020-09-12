#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <string_view>
#include <algorithm>
#include <functional>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other)
    {
        for (const auto& pair : other.word_frequences)
        {
            word_frequences[pair.first] += pair.second;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    std::string_view line_view = line;
    Stats result;

    size_t pos = line_view.find_first_not_of(' ');
    line_view.remove_prefix(pos);

    while (pos != line_view.npos)
    {
        pos = line_view.find_first_of(' ');

        auto key = std::string(line_view.substr(0, pos));

        if (key_words.count(key) > 0)
        {
            ++result.word_frequences[std::move(key)];
        }

        if (pos == line_view.npos)
            break;

        line_view.remove_prefix(pos);
        pos = line_view.find_first_not_of(' ');
        line_view.remove_prefix(pos);
    }

    return result;
}

Stats ExploreKeyWordsSingleThread(
    const set<string>& key_words, istream& input
) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    std::vector<std::future<Stats>> futures;
    size_t num_lines = 0;
    const auto num_threads = std::thread::hardware_concurrency();
    std::vector<std::stringstream> streams(num_threads);

    std::string line;
    while (std::getline(input, line))
    {
        streams[num_lines % num_threads] << line << '\n';
        ++num_lines;
    }

    for (auto& s : streams)
    {
        futures.push_back(std::async([&]
            {
                return ExploreKeyWordsSingleThread(key_words, s);
            }));
    }

    for (auto& future : futures)
    {
        result += future.get();
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
      {"yangle", 6},
      {"rocks", 2},
      {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}