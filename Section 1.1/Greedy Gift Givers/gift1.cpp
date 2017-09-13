/*
 ID: tushar.4
 PROG: gift1
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
  ofstream fout("gift1.out");
  ifstream fin("gift1.in");
  
  int np{0};
  string line{};
  
  getline(fin, line);
  stringstream(line) >> np;
  
  if(np == 0) return 0;
  
  unordered_map<string, int> records;
  
  vector<string> names(np);
  for(int i = 0; i < np; ++i){
    getline(fin, line);
    names[i] = line;
    records[line] = 0;
  }
  
  
  line = "";
  getline(fin, line);
  
  while(!line.empty()){
    string name{line};
    
    int amount{0};
    int givers{0};
    getline(fin, line);
    stringstream(line) >> amount >> givers;
    
    records[name] += amount > 0 ? amount * -1 : amount;
    
    int share_per_person{0};
    if(givers != 0)
      share_per_person = amount / givers;
    
    int remaining = amount - (share_per_person * givers);
    
    records[name] += remaining;
    
    for(int j = 0; j < givers; ++j){
      getline(fin, line);
      records[line] += share_per_person;
    }
    
    getline(fin, line);
  }
  
  for(const auto& name : names){
    fout << name << ' ' << records[name] << '\n';
  }
  
  return 0;
}

