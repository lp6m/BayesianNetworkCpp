#include <bits/stdc++.h>
#include "Column.h"
using namespace std;

Column::Column(string m_name): name(m_name){

}

vector<int> Column::get_kinds(){
  return vector<int>(this->value_kind_set.begin(), this->value_kind_set.end());
}
int Column::get_kind_num(){
  return this->value_kind_set.size();
}

void Column::update_kind_num(int val){
  this->value_kind_set.insert(val);
}
