#include <bits/stdc++.h>
#include "Column.h"

using namespace std;

#ifndef Define_DataSet
#define Define_DataSet

class DataSet{
public:
  vector<vector<int>> data;
  void set_data(vector<string>&, vector<vector<int>>&);
  void set_data_fromfile(string);
  int get_column_index_from_name(string);
  vector<Column> columns;
private:
  void add_data(vector<int>&);
  void set_column(vector<string>&);
  map<string, int> column_index_of_name; 
};

#endif
