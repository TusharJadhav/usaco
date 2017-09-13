/*
ID: tushar.4
PROG: milk2
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

int main()
{
  ofstream fout("milk2.out");
  ifstream fin("milk2.in");

  int n{ 0 };
  fin >> n;

  vector<pair<int, int>> schedule(n);

  for (int i = 0; i < n; ++i) {
    int start{ 0 };
    int end{ 0 };

    fin >> start >> end;
    schedule[i] = make_pair(start, end);
  }

  sort(schedule.begin(), schedule.end(), [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.first <= right.first;
  });

  vector<pair<int, int>> compressed_schedule;

  for (const auto& current : schedule) {
    if (compressed_schedule.empty()) {
      compressed_schedule.push_back(current);
      continue;
    }

    auto last = compressed_schedule.back();
    if (current.first <= last.second && current.second > last.second) {
      pair<int, int> new_element(last.first, current.second);
      compressed_schedule.pop_back();
      compressed_schedule.push_back(new_element);
    }
    else 
    if (current.first <= last.second && current.second <= last.second) {
      continue;
    } 
    else {
      compressed_schedule.push_back(current);
    }
  }

  long longest_continous_milking{ 0 };
  long longest_idle_time{ 0 };

  if (compressed_schedule.size() != 0) {
    if (compressed_schedule.size() == 1) {
      longest_continous_milking = compressed_schedule.front().second - compressed_schedule.front().first;
    }
    else {
      for (int i = 0; i < static_cast<int>(compressed_schedule.size()); ++i) {
        longest_continous_milking = max(longest_continous_milking, static_cast<long>(compressed_schedule[i].second - compressed_schedule[i].first));

        if (i > 0) {
          longest_idle_time = max(longest_idle_time, static_cast<long>(compressed_schedule[i].first - compressed_schedule[i - 1].second));
        }
      }
    }
  }

  fout << longest_continous_milking << ' ' << longest_idle_time << '\n';
  return 0;
}
