/*
 ID: tushar.4
 PROG: namenum
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

void get_permutations_impl(const vector<vector<char>>& sets,
                           const unordered_set<string>& dict,
                           string& word,
                           vector<string>& words) {
  
  const auto& set = sets[word.size()];
  
  for(const auto& ch : set){
    word.push_back(ch);
    
    if(word.size() == sets.size()){
      if(dict.find(word) != dict.end()){
        words.push_back(word);
      }
    }
    else{
      get_permutations_impl(sets, dict, word, words);
    }
    
    if(!word.empty())
      word.pop_back();
  }
}

vector<string> get_permutations(const vector<vector<char>>& sets, const unordered_set<string>& dict) {
  string word;
  vector<string> words;
  
  get_permutations_impl(sets, dict, word, words);
  return words;
}

int main()
{
  ofstream fout("namenum.out");
  ifstream fin("namenum.in");
  ifstream dict_in("dict.txt");
  
  string dict_word{""};
  dict_in >> dict_word;
  unordered_set<string> dict;
  
  while (!dict_word.empty()) {
    dict.insert(dict_word);
    dict_word.clear();
    dict_in >> dict_word;
  }
  
  unordered_map<int, vector<char>> keypad_mapping{
    {2, {'A', 'B', 'C'}},
    {3, {'D', 'E', 'F'}},
    {4, {'G', 'H', 'I'}},
    {5, {'J', 'K', 'L'}},
    {6, {'M', 'N', 'O'}},
    {7, {'P', 'R', 'S'}},
    {8, {'T', 'U', 'V'}},
    {9, {'W', 'X', 'Y'}}};
  
  
  string input{""};
  fin >> input;
  
  vector<vector<char>> sets;
  for(const auto& ch : input){
    int num = ch - '0';
    sets.push_back(keypad_mapping[num]);
  }
  
  vector<string> final_words = get_permutations(sets, dict);
  
  sort(final_words.begin(), final_words.end());
  
  if(final_words.empty()){
    fout << "NONE" << '\n';
  }
  else{
    for(const auto& final_word : final_words){
      fout << final_word << '\n';
    }
  }
  
  return 0;
}
