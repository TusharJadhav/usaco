/*
ID: tushar.4
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <forward_list>
#include <list>
#include <stack>
#include <algorithm>
#include <functional>
#include <limits>
#include <memory>
#include <tuple>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <bitset>

using namespace std;

class Friday {
private:
  typedef enum class tagMonth {
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    Novemeber = 11,
    December = 12
  } Month;

  typedef enum class tagDay {
    Saturday = 0,
    Sunday = 1,
    Monday = 2,
    Tuesday = 3,
    Wednesday = 4,
    Thursday = 5,
    Friday = 6
  } Day;

  bool is_centuary_year(int year) {
    return year % 100 == 0;
  }

  bool is_leap_year(int year) {
    if (is_centuary_year(year))
      return year % 400 == 0 ? true : false;

    return year % 4 == 0;
  }

  int get_days_of_month(Month month, int year) {
    if (month == Month::September || month == Month::April || month == Month::June || month == Month::Novemeber)
      return 30;

    if (month == Month::February)
      return is_leap_year(year) ? 29 : 28;

    return 31;
  }

public:
  vector<int> solve(int n) {
    vector<int> frequencies(7, 0);
    auto start_day_of_month = Day::Monday;

    for (int year = 1900; year < 1900 + n; ++year) {
      for (int month = 1; month <= 12; ++month) {
        auto thirteenth_happens_to_be_on = static_cast<Day>((static_cast<int>(start_day_of_month) + 12) % 7);
        frequencies[static_cast<int>(thirteenth_happens_to_be_on)] += 1;

        auto days_of_month = get_days_of_month(static_cast<Month>(month), year);

        start_day_of_month = static_cast<Day>((static_cast<int>(start_day_of_month) + days_of_month) % 7);
      }
    }
    return frequencies;
  }
};

int main()
{
  ifstream fin("friday.in");
  int n;
  fin >> n;
  fin.close();

  ofstream fout("friday.out");
  auto result = Friday().solve(n);

  std::stringstream ss_result;
  for (const auto& freq : result) {
    ss_result << freq << " ";
  }

  auto str_result = ss_result.str();
  fout << str_result.substr(0, str_result.length() - 1) << "\n";
  fout.close();

  return 0;
}
