/*
ID: tushar.4
PROG: barn1
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
  ofstream fout("barn1.out");
  ifstream fin("barn1.in");

  int max_boards{ 0 }, no_of_stalls{ 0 }, no_of_cows{ 0 };
  fin >> max_boards >> no_of_stalls >> no_of_cows;

  vector<int> occupied_stalls(no_of_cows);

  for (int index = 0; index < no_of_cows; ++index) {
    fin >> occupied_stalls[index];
  }

  sort(occupied_stalls.begin(), occupied_stalls.end());

  vector<int> cows, empty;
  if (occupied_stalls.size() != 0)
    cows.push_back(1);

  for (size_t index = 1; index < occupied_stalls.size(); ++index) {
    if (occupied_stalls[index] == occupied_stalls[index - 1] + 1) {
      if (cows.size() != 0)
        ++cows.back();
      else
        cows.push_back(1);
    }
    else {
      empty.push_back(occupied_stalls[index] - occupied_stalls[index - 1] - 1);
      cows.push_back(1);
    }
  }

  int result{ no_of_cows };

  if (cows.size() > max_boards) {
    sort(empty.begin(), empty.end(), [](const int& left, const int& right) {
      return left > right;
    });

    size_t count = cows.size();

    while (count != max_boards) {
      result += empty.back();
      empty.pop_back();
      --count;
    }
  }

  fout << result << endl;

  return 0;
}
