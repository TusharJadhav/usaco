/*
ID: tushar.4
PROG: dualpal
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

string get_number(long long num_base_10, int base) {
  static unordered_map<int, char> dict{ {0, '0'}, {1, '1'}, { 2, '2' }, { 3, '3' }, { 4, '4' }, { 5, '5' }, { 6, '6' }, { 7, '7' }, { 8, '8' },
  { 9, '9' }, { 10, 'A' }, { 11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}, {16, 'G'}, {17, 'H'}, {18, 'I'}, {19, 'J'}, {20, 'K'} };

  stringstream ss_result;
  do {
    long long digit = num_base_10 / base;
    ss_result << dict[num_base_10 % base];
    num_base_10 = digit;
  } while (num_base_10 != 0);

  auto result = ss_result.str();
  reverse(result.begin(), result.end());
  return result;
}

bool is_palindrome(const string& str) {
  if (str.length() <= 1)
    return true;

  auto fwd = str.cbegin();
  auto rev = str.crbegin();

  size_t fwd_idx = distance(str.cbegin(), fwd);
  size_t rev_idx = str.length() -  distance(str.crbegin(), rev);

  while (fwd_idx < rev_idx) {
    if (*fwd != *rev)
      return false;

    ++fwd;
    ++rev;

    fwd_idx = distance(str.cbegin(), fwd);
    rev_idx = str.length() - distance(str.crbegin(), rev);
  }

  return true;
}

int main()
{
  ofstream fout("dualpal.out");
  ifstream fin("dualpal.in");

  int n, s;
  fin >> n >> s;

  int curr = s + 1;
  int found = 0;

  while (n != 0) {
    for (int base = 2; base <= 10; ++base) {
      string number;
      if (base == 10)
        number = to_string(curr);
      else
        number = get_number(curr, base);

      if (*number.cbegin() == '0' || *number.crbegin() == '0')
        continue;

      if (is_palindrome(number)) {
        ++found;
      }

      if (found == 2) {
        fout << curr << '\n';
        --n;
        break;
      }
    }

    found = 0;
    ++curr;
  }

  return 0;
}
