/*
ID: tushar.4
PROG: crypt1
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

bool is_valid(int number, int expected_digits, const unordered_set<int>& set) {
  int actual_digits{ 0 };

  while (number != 0) {
    int digit = number % 10;
    if (set.find(digit) == set.end())
      return false;

    number /= 10;
    ++actual_digits;
  };

  return actual_digits == expected_digits;
}

int main()
{
  ofstream fout("crypt1.out");
  ifstream fin("crypt1.in");

  int n{ 0 };
  fin >> n;

  vector<int> vec(n);
  unordered_set<int> set;
  for (int index = 0; index < n; ++index) {
    int no;
    fin >> no;
    vec[index] = no;
    set.insert(no);
  }

  int result{ 0 };

  for (int a2 = 0; a2 < n; ++a2) {
    for (int a1 = 0; a1 < n; ++a1) {
      for (int a0 = 0; a0 < n; ++a0) {
        for (int b1 = 0; b1 < n; ++b1) {
          for (int b0 = 0; b0 < n; ++b0) {
            int first = (vec[a2] * 100) + (vec[a1] * 10) + vec[a0];
            int second = (vec[b1] * 10) + vec[b0];

            int inter1 = vec[b0] * first;
            if (!is_valid(inter1, 3, set))
              continue;

            int inter2 = vec[b1] * first;
            if (!is_valid(inter2, 3, set))
              continue;

            int product_result = inter1 + (inter2 * 10);
            if (!is_valid(product_result, 4, set))
              continue;

            ++result;
          }
        }
      }
    }
  }

  fout << result << endl;

  return 0;
}
