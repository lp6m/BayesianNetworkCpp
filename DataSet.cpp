#include <bits/stdc++.h>
#include "Column.h"
#include "DataSet.h"
#include "Util.h"
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

int DataSet::set_data_fromfile(string filename){
  ifstream ifs(filename);
  string str;
  if (ifs.fail()){
    cout << "open dataset file failed" << endl;
    return -1;
  }
  bool is_firstline = true;
  vector<string> column_names;
  vector<vector<int>> data;
  while (getline(ifs, str)){
    vector<string> items = Util::string_split(str, ',');
    vector<int> oneline_data;
    for(string item: items){
      item = Util::string_trim(item);
      if(is_firstline) column_names.push_back(item);
      else{
        int val = -1;
        if(item == "yes") val = 1;
        else if(item == "no") val = 0;
        oneline_data.push_back(val);
        data.push_back(oneline_data);
      }
    }
    is_firstline = false;
  }
  this->set_data(column_names, data);
  return 0;
}

