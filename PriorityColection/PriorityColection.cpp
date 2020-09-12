#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = int;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object);

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin);

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const;

    // Получить объект по идентификатору
    const T& Get(Id id) const;

    // Увеличить приоритет объекта на 1
    void Promote(Id id);

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const;

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax();

private:
    // Приватные поля и методы
    struct Object
    {
        T data;
        int priority = 0;
    };

    static const int InvalidPriority = -1;

    vector<Object> objects;
    set<pair<int, Id>> sort_object;
};

template<typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object)
{
    const Id prior = objects.size();
    objects.push_back({ move(object) });
    sort_object.insert({ 0, prior });
  
    return prior;
}

template<typename T>
bool PriorityCollection<T>::IsValid(Id id) const
{
    return id >= 0 && objects.size() > id && objects[id].priority != InvalidPriority;
}

template<typename T>
const T& PriorityCollection<T>::Get(Id id) const
{
    return objects[id].data;
}

template<typename T>
void PriorityCollection<T>::Promote(Id id)
{
    auto& temp = objects[id];
    const int for_erase = temp.priority;
    const int for_add = ++temp.priority;
    sort_object.erase({ for_erase, id });
    sort_object.insert({ for_add, id });
}

template<typename T>
pair<const T&, int> PriorityCollection<T>::GetMax() const
{
    auto& item = objects[prev(sort_object.end())->second];

    return {item.data, item.priority};
}

template<typename T>
pair<T, int> PriorityCollection<T>::PopMax()
{
    const auto it = prev(sort_object.end());
    auto& item = objects[it->second];
    sort_object.erase(it);
    auto prior = item.priority;
    item.priority = InvalidPriority;

    return {move(item.data), prior};
}



class StringNonCopyable : public string {
public:
    using string::string;  // РџРѕР·РІРѕР»СЏРµС‚ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹ СЃС‚СЂРѕРєРё
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}

template<typename T>
template<typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
{
    while (range_begin != range_end)
        *ids_begin++ = Add(move(*range_begin++));
}
