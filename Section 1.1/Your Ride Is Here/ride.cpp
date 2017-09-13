/*
 ID: tushar.4
 PROG: ride
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
  ofstream fout("ride.out");
  ifstream fin("ride.in");
  
  string input1, input2;
  fin >> input1 >> input2;
  
  long result1{1}, result2{1};
  
  for(const auto& ch1 : input1){
    result1 *= (ch1 - 'A') + 1;
    result1 = (result1 % 47);
  }
  
  for(const auto& ch2 : input2){
    result2 *= (ch2 - 'A') + 1;
    result2 = (result2 % 47);
  }
  
  fout << ((result1 == result2) ? "GO" : "STAY") << endl;
  
  return 0;
}

