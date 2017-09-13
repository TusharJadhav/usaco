/*
ID: tushar.4
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

class wormhole {
  private:
    vector<pair<int, int>> input_locations_;
    vector<int> paired_;
    vector<int> right_of_;

  public:
    wormhole(vector<pair<int, int>> input_locations) :
      input_locations_{ move(input_locations) },
      paired_(input_locations_.size(), 0),
      right_of_(input_locations_.size(), 0)
    {
      for(size_t i = 1; i <= input_locations_.size() - 1; ++i)
        for(size_t j = 1; j <= input_locations_.size() - 1; ++j)
          if(input_locations_[j].second == input_locations_[i].second && input_locations_[i].first !=
            input_locations_[j].first &&input_locations_[j].first > input_locations_[i].first )
            if( right_of_[i] == 0 || 
              input_locations_[j].first - input_locations_[i].first < input_locations_[right_of_[i]].first -
              input_locations_[i].first) {
              right_of_[i] = j;
            }
    }

    size_t solve() {
      //Iterate over all possible pairs of wormholes recursively and add ones that form a cycle

      // Find the first non-paired worm hole
      size_t i = 1;
      for( ;i <= paired_.size() - 1; ++i)
        if( paired_[i] == 0 )
          break;

      if(i > paired_.size() - 1)
        return cycle_exists() ? 1 : 0;

      size_t total = 0;

      // Pair the first non-paired wormhole with the rest of non-paired wormholes
      for(size_t j = i + 1; j <= paired_.size() - 1; ++j) {
        if(paired_[j] == 0) {
          paired_[i] = j;
          paired_[j] = i;

          total += solve();

          paired_[i] = 0;
          paired_[j] = 0;
        }
      }

      return total;
    }

    private:
      bool cycle_exists() {
        for(size_t i = 1; i <= input_locations_.size() - 1; ++i) {
          auto start = i;

          for(size_t j = 1; j <= input_locations_.size() - 1; ++j) {
            start = right_of_[paired_[start]];
          }

          if(start != 0)
            return true;
        }

        return false;
      }
};

int main() {
  ifstream fin("wormhole.in");
  int n;
  fin >> n;

  vector<pair<int, int>> wormholes_loc(n + 1, {0, 0});

  for(int i = 1; i <= n; ++i)
    fin >> wormholes_loc[i].first >> wormholes_loc[i].second;
  
  ofstream fout("wormhole.out");
  fout << wormhole(move(wormholes_loc)).solve() << "\n";

  return 0;
}
