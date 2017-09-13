/*
ID: tushar.4
PROG: combo
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

// Wrap number num in range [lower_bound, upper_bound]
int wrap(int num, int lower_bound, int upper_bound) {
  if (lower_bound == upper_bound)
    return lower_bound;

  int range = upper_bound - lower_bound + 1;

  if (num < lower_bound) {
    int offset = abs(num - lower_bound);
    return range - offset + 1;
  }
  else
    if (num > upper_bound) {
      int offset = abs(num - upper_bound);
      return lower_bound + offset - 1;
    }

  return num;
}

string get_lock(const vector<int>& lock) {
  string result{};
  for (const auto no : lock) {
    result += to_string(no);
    result += "-";
  }

  return result.substr(0, result.size() - 1);
}

void get_lock_combinations_impl(const vector<vector<int>>& valid_numbers, unordered_set<string>& dict, vector<int>& current_lock) {
  if (current_lock.size() == 3) {
    auto lk = get_lock(current_lock);
    if (dict.find(lk) == dict.end())
      dict.insert(lk);
    return;
  }

  auto vec = valid_numbers[current_lock.size()];
  for (int i = 0; i < vec.size(); ++i) {
    current_lock.push_back(vec[i]);
    get_lock_combinations_impl(valid_numbers, dict, current_lock);
    current_lock.pop_back();
  }
}

void get_lock_combinations(const vector<vector<int>>& valid_numbers, unordered_set<string>& dict) {
  vector<int> current_lock {};
  return get_lock_combinations_impl(valid_numbers, dict, current_lock);
}

int main()
{
  ofstream fout("combo.out");
  ifstream fin("combo.in");

  int n{ 0 };
  fin >> n;

  vector<vector<int>> farmers_combo;
  
  for (int i = 0; i < 3; ++i) {
    int no;
    fin >> no;

    vector<int> combinations;
    for (int cnt = no - 2; cnt <= no + 2; ++cnt) {
      combinations.push_back(wrap(cnt, 1, n));
    }

    farmers_combo.push_back(combinations);
  }

  vector<vector<int>> master_combo;

  for (int i = 0; i < 3; ++i) {
    int no;
    fin >> no;

    vector<int> combinations;
    for (int cnt = no - 2; cnt <= no + 2; ++cnt) {
      combinations.push_back(wrap(cnt, 1, n));
    }

    master_combo.push_back(combinations);
  }

  unordered_set<string> dict;
  get_lock_combinations(farmers_combo, dict);
  if(farmers_combo != master_combo)
    get_lock_combinations(master_combo, dict);

  fout << dict.size() << endl;

  return 0;
}
