#include <bits/stdc++.h>
#include "Node.h"
#include "BaysianNetwork.h"
#include "Column.h"
#include "DataSet.h"
#include "BdeuScore.h"
#include "util.h"

using namespace std;

int main(){
  BayesianNetwork bn;
  vector<string> node_ames;
  int node_num, edge_num;
  cin >> node_num >> edge_num;
  vector<string> column_names;
  REP(i, node_num){
    string column_name;
    cin >> column_name;
    column_names.push_back(column_name);
  }
  REP(i, edge_num){
    string from, to;
    cin >> from >> to;
    bn.add_edge(from, to);
  }
  bn.show_nodes();
  
  bn.save_as_dotscript("graph.dot");

  int data_num;
  cin >> data_num;
  vector<vector<int>> dataarr;
  REP(i, data_num){
    vector<int> oneline;
    REP(j, column_names.size()){
      int val;
      cin >> val;
      oneline.push_back(val);
    }
    dataarr.push_back(oneline);
  }

  DataSet dataset;
  dataset.set_data(column_names, dataarr);
  REP(i, column_names.size()){
    cout << dataset.columns[i].name << " : ";
    cout << dataset.columns[i].get_kind_num() << endl;
  }

  BdeuScore bdeuscore(bn, dataset);
  double score = bdeuscore.get_score();
  cout << score << endl;
}
