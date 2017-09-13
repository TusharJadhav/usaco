/*
ID: tushar.4
PROG: beads
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
  ofstream fout("beads.out");
  ifstream fin("beads.in");

  int n{ 0 };
  string line{}, beads{};

  getline(fin, line);
  stringstream(line) >> n;

  getline(fin, line);
  stringstream(line) >> beads;

  beads += beads;

  vector<pair<int, int>> left((2 * n) + 1, { 0, 0 });

  for (int i = 1; i <= 2 * n; i++) {
    if (beads[i - 1] == 'r') {
      left[i].first = left[i - 1].first + 1;
      left[i].second = 0;
    }
    else if (beads[i - 1] == 'b') {
      left[i].first = 0;
      left[i].second = left[i - 1].second + 1;
    }
    else {
      left[i].first = left[i - 1].first + 1;
      left[i].second = left[i - 1].second + 1;
    }
  }

  vector<pair<int, int>> right(( 2 * n) + 1, { 0, 0 });

  for (int i = 2 * n - 1; i >= 0; i--) {
    if (beads[i] == 'r') {
      right[i].first = right[i + 1].first + 1;
      right[i].second = 0;
    }
    else if (beads[i] == 'b') {
      right[i].first = 0;
      right[i].second = right[i + 1].second + 1;
    }
    else {
      right[i].first = right[i + 1].first + 1;
      right[i].second = right[i + 1].second + 1;
    }
  }

  int result{ 0 };
  for (int i = 0; i < static_cast<int>(left.size()); ++i) {
    int temp = max(left[i].first, left[i].second) +
      max(right[i].first, right[i].second);

    result = max(result, temp);
  }

  result = min(result, n);

  fout << result << '\n';

  return 0;
}
