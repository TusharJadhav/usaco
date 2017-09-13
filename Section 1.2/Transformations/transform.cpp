/*
ID: tushar.4
PROG: transform
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

void cyclic_shift(char& a, char& b, char& c, char& d) {
  char temp = a;
  a = b;
  b = c;
  c = d;
  d = temp;
}

void rotate_by_90_degrees(vector<vector<char>>& matrix) {
  size_t no_of_rows = matrix.size();
  size_t no_of_cols = matrix.begin()->size();

  for (size_t row = 0; row < no_of_rows / 2; ++row) {
    for (size_t col = 0; col < (no_of_cols + 1) / 2; ++col) {
      cyclic_shift(matrix[row][col], 
                   matrix[no_of_cols - 1 - col][row],
                   matrix[no_of_rows - 1 - row][no_of_cols - 1 - col],
                   matrix[col][no_of_rows - 1 - row]
                   );
    }
  }
}

bool are_same(const vector<vector<char>>& left, const vector<vector<char>>& right) {
  if (left.size() != right.size())
    return false;

  if (left.begin()->size() != right.begin()->size())
    return false;

  for (size_t row = 0; row < left.size(); ++row) {
    for (size_t col = 0; col < left.begin()->size(); ++col) {
      if (left[row][col] != right[row][col])
        return false;
    }
  }

  return true;
}

vector<vector<char>> read_matrix(size_t dim, ifstream& fin) {
  vector<vector<char>> matrix(dim, vector<char>(dim));

  for (size_t row = 0; row < dim; ++row) {
    for (size_t col = 0; col < dim; ++col) {
      fin >> matrix[row][col];
    }
  }

  return matrix;
}

void reflect_vertically(vector<vector<char>>& matrix) {
  for (size_t col = 0; col < matrix.begin()->size() / 2; ++col) {
    for (size_t row = 0; row < matrix.size(); ++row) {
      swap(matrix[row][col], matrix[row][matrix.begin()->size() - 1 - col]);
    }
  }
}

void reflect_horizontally(vector<vector<char>>& matrix) {
  for (size_t row = 0; row < matrix.size() / 2; ++row) {
    for (size_t col = 0; col < matrix.begin()->size(); ++col) {
      swap(matrix[row][col], matrix[matrix.size() - 1 - row][col]);
    }
  }
}

int main()
{
  ofstream fout("transform.out");
  ifstream fin("transform.in");

  size_t n{ 0 };
  fin >> n;

  auto before = read_matrix(n, fin);
  auto after = read_matrix(n, fin);

  int result{ 7 };
  bool same_as_orignal{ false };
  auto before_dup{ before };
  if (are_same(before, after))
    same_as_orignal = true;

  rotate_by_90_degrees(before);
  if (are_same(before, after))
    result = 1;

  if (result == 7) {
    rotate_by_90_degrees(before);
    if (are_same(before, after))
      result = 2;
  }

  if (result == 7) {
    rotate_by_90_degrees(before);
    if (are_same(before, after))
      result = 3;
  }

  if (result == 7) {
    before = before_dup;
    reflect_vertically(before);
    if (are_same(before, after))
      result = 4;
  }

  if (result == 7) {
    rotate_by_90_degrees(before);
    if (are_same(before, after))
      result = 5;

    if (result == 7) {
      rotate_by_90_degrees(before);
      if (are_same(before, after))
        result = 5;
    }

    if (result == 7) {
      rotate_by_90_degrees(before);
      if (are_same(before, after))
        result = 5;
    }
  }

  if (result == 7 && same_as_orignal)
    result = 6;

  fout << result << '\n';

  return 0;
}
