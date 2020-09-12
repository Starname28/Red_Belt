#include <iomanip>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>

using namespace std;

class ReadingManager {
private:

    map<uint64_t, uint16_t> id_pages;
    unordered_map<uint16_t, set<uint64_t>> pages_id;
public:
    ReadingManager(){}

    void Read(int user_id, int page_count) {
        if (id_pages.count(user_id))
        {
            uint16_t page_by_id = id_pages[user_id];
            pages_id[page_by_id].erase(user_id);

            if (pages_id[page_by_id].size() == 0)
                pages_id.erase(page_by_id);
        }
        
        id_pages[user_id] = page_count;
        pages_id[page_count].insert(user_id);

    }

    double Cheer(int user_id) const {
        //    if (!id_pages.count(user_id))
        //    {
        //        return 0;
        //    }

        //    uint64_t count = id_pages.size();

        //    if (count == 1)
        //        return 1;

        //  /*  if (user_count == 1) {
        //        return 1;
        //    }
        //    const int page_count = user_page_counts_[user_id];
        //    int position = user_positions_[user_id];
        //    while (position < user_count &&
        //        user_page_counts_[sorted_users_[position]] == page_count) {
        //        ++position;
        //    }
        //    if (position == user_count) {
        //        return 0;
        //    }*/
        //    auto it = pages_id.find(id_pages.at(user_id));
        //    //int sum = 0;
        //    ///*cout << "-------" << endl;
        //    //for (auto ch : it->second)
        //    //    cout << ch << ' ';
        //    //cout <<endl<< "-------" <<  endl;*/
        //    int sum = 0;
        //    for (auto iter = next(it); iter != pages_id.end(); iter++)
        //        sum += iter->second.size();

        //    double ret = (distance(pages_id.begin(), it) * 1.0) / (count - 1);//*/ );;//it->second.size());
        //    // По умолчанию деление целочисленное, поэтому
        //    // нужно привести числитель к типу double.
        //    // Простой способ сделать это — умножить его на 1.0.
        //    return ret;
        //}
        const auto count_ = id_pages.count(user_id);

        if (id_pages.size() == 1 && count_ == 1)
        {
            return 1;
        }

        if (count_ == 0)
        {
            return 0;
        }

        const int current_page = id_pages.at(user_id);

        auto pos = pages_id.find(current_page);

        if (pos == pages_id.begin())
        {
            return 0;
        }

        --pos;

        double res = 0;

        do
        {
            res += pos->second.size();

            if (pos == pages_id.begin())
                break;

            --pos;
        } while (true);

        return res / (pages_id.size() - 1);
    }
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}