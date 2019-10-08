#include <bits/stdc++.h>
#include "Column.h"
#include "DataSet.h"
#include "util.h"
using namespace std;

void DataSet::set_column(vector<string>& columns){
  int i = 0;
  for(string name: columns){
    this->columns.push_back(Column(name));
    this->column_index_of_name[name] = i++;
  }
}

int DataSet::get_column_index_from_name(string name){
  return this->column_index_of_name[name];
}
void DataSet::add_data(vector<int>& oneline){
  data.push_back(oneline);
  REP(i, oneline.size()){
    int val = oneline[i];
    this->columns[i].update_kind_num(val);
  }
}

void DataSet::set_data(vector<string>& column_names, vector<vector<int>>& data){
  this->set_column(column_names);
  for(vector<int> oneline : data){
    this->add_data(oneline);
  }
}

void DataSet::set_data_fromfile(string filename){
  //TODO
}

