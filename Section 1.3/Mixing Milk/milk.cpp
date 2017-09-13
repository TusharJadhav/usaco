/*
ID: tushar.4
PROG: milk
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
  typedef struct tagSeller {
    int price_per_unit;
    int total_units;
  } Seller;

  ofstream fout("milk.out");
  ifstream fin("milk.in");

  int demand, no_of_farmers;
  fin >> demand >> no_of_farmers;

  vector<Seller> sellers(no_of_farmers);

  for (int cnt = 0; cnt < no_of_farmers; ++cnt) {
    fin >> sellers[cnt].price_per_unit >> sellers[cnt].total_units;
  }

  sort(sellers.begin(), sellers.end(), [](const Seller& left, const Seller& right) {
    return left.price_per_unit < right.price_per_unit;
  });

  long cost{ 0 };
  for (const auto& seller : sellers) {
    if (demand == 0)
      break;

    long curr_units_to_purchase{ 0 };

    if (demand > seller.total_units)
      curr_units_to_purchase = seller.total_units;
    else
      curr_units_to_purchase = demand;

    cost += (seller.price_per_unit * curr_units_to_purchase);
    demand -= curr_units_to_purchase;
  }

  fout << cost << endl;

  return 0;
}
