#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    // РџРѕ СѓРјРѕР»С‡Р°РЅРёСЋ РґРµР»РµРЅРёРµ С†РµР»РѕС‡РёСЃР»РµРЅРЅРѕРµ, РїРѕСЌС‚РѕРјСѓ
    // РЅСѓР¶РЅРѕ РїСЂРёРІРµСЃС‚Рё С‡РёСЃР»РёС‚РµР»СЊ Рє С‚РёРїСѓ double.
    // РџСЂРѕСЃС‚РѕР№ СЃРїРѕСЃРѕР± СЃРґРµР»Р°С‚СЊ СЌС‚Рѕ вЂ” СѓРјРЅРѕР¶РёС‚СЊ РµРіРѕ РЅР° 1.0.
    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:
  // РЎС‚Р°С‚РёС‡РµСЃРєРѕРµ РїРѕР»Рµ РЅРµ РїСЂРёРЅР°РґР»РµР¶РёС‚ РєР°РєРѕРјСѓ-С‚Рѕ РєРѕРЅРєСЂРµС‚РЅРѕРјСѓ
  // РѕР±СЉРµРєС‚Сѓ РєР»Р°СЃСЃР°. РџРѕ СЃСѓС‚Рё СЌС‚Рѕ РіР»РѕР±Р°Р»СЊРЅР°СЏ РїРµСЂРµРјРµРЅРЅР°СЏ,
  // РІ РґР°РЅРЅРѕРј СЃР»СѓС‡Р°Рµ РєРѕРЅСЃС‚Р°РЅС‚РЅР°СЏ.
  // Р‘СѓРґСЊ РѕРЅР° РїСѓР±Р»РёС‡РЅРѕР№, Рє РЅРµР№ РјРѕР¶РЅРѕ Р±С‹Р»Рѕ Р±С‹ РѕР±СЂР°С‚РёС‚СЊСЃСЏ СЃРЅР°СЂСѓР¶Рё
  // СЃР»РµРґСѓСЋС‰РёРј РѕР±СЂР°Р·РѕРј: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // РѕС‚СЃРѕСЂС‚РёСЂРѕРІР°РЅС‹ РїРѕ СѓР±С‹РІР°РЅРёСЋ РєРѕР»РёС‡РµСЃС‚РІР° СЃС‚СЂР°РЅРёС†
  vector<int> user_positions_; // РїРѕР·РёС†РёРё РІ РІРµРєС‚РѕСЂРµ sorted_users_

  int GetUserCount() const {
    return sorted_users_.size();
  }
  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};


int main() {
  // Р”Р»СЏ СѓСЃРєРѕСЂРµРЅРёСЏ С‡С‚РµРЅРёСЏ РґР°РЅРЅС‹С… РѕС‚РєР»СЋС‡Р°РµС‚СЃСЏ СЃРёРЅС…СЂРѕРЅРёР·Р°С†РёСЏ
  // cin Рё cout СЃ stdio,
  // Р° С‚Р°РєР¶Рµ РІС‹РїРѕР»РЅСЏРµС‚СЃСЏ РѕС‚РІСЏР·РєР° cin РѕС‚ cout
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
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}