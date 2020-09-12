// Sort_By_Macro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

#define SORT_BY(field) [](const AirlineTicket& lhs, const AirlineTicket& rhs){return lhs.field < rhs.field;} // � еализуйте этот макрос, а также необходимые операторы для классов Date и Time


#define UPDATE_FIELD(ticket, field, values) \
{\
  auto it = values.find(#field);\
if (it != values.end()) {       \
    istringstream is(it->second);\
    is >> ticket.field;\
}\
}


bool operator>(const Date& lhs, const Date& rhs)
{
    return (lhs.year > rhs.year) &&
        (lhs.month > rhs.month) &&
        (lhs.day > rhs.day);
}

bool operator<(const Date& lhs, const Date& rhs)
{

    return      tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);

}
bool operator<(const Time& lhs, const Time& rhs)
{
    return (lhs.hours <= rhs.hours) &&
        (lhs.minutes < rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs)
{
    return (lhs.hours == rhs.hours) &&
        (lhs.minutes == rhs.minutes);
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return (lhs.year == rhs.year) &&
        (lhs.month == rhs.month) &&
        (lhs.day == rhs.day);
}


ostream& operator<<(ostream& os, const Date& date)
{
    return os << date.year << date.month  << date.day;
}

ostream& operator<<(ostream& os, const Time& time)
{
    return os << time.hours << ':' << time.minutes;
}

istream& operator>>(istream& is, Time& time)
{
    string s;
    getline(is, s, ':');
    time.hours = atoi(s.c_str());
    getline(is, s);
    time.minutes = atoi(s.c_str());
    return is;
}

istream& operator>>(istream& is, Date& date)
{
    string s;
    getline(is, s, '-');
    date.year = atoi(s.c_str());
    getline(is, s, '-');
    date.month = atoi(s.c_str());
    getline(is, s);
    date.day = atoi(s.c_str());
;
    return is;
}
  // � еализуйте этот макрос, а также необходимые операторы для классов Date и Time

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}