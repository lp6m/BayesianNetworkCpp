#include <bits/stdc++.h>
using namespace std;

#ifndef Define_Column
#define Define_Column

class Column{
public:
  Column(string);
  string name;
  int get_kind_num();
  void update_kind_num(int);
  vector<int> get_kinds();
private:
  set<int> value_kind_set; //number of kind of data
};

#endif
