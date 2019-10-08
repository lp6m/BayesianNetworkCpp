#include <bits/stdc++.h>
#include "Node.h"
#include "BaysianNetwork.h"
#include "BdeuScore.h"
#include "Column.h"
#include "StructureLearning.h"
#include "DataSet.h"
#include "Util.h"

using namespace std;

int main(){
  StructureLearning sl;
  DataSet dataset;
  dataset.set_data_fromfile("dataset/asia10K.csv");
  cout << "DataSet score load end" << endl;
  BdeuScore bdeuscore2(dataset);

  vector<Node> nodes;
  vector<string> node_names = {"Smoker", "LungCancer", "VisitToAsia", "Tuberculosis", "TuberculosisOrCancer", "X-ray", "Bronchitis", "Dyspnea"};
  for(string node_name: node_names){
    nodes.push_back(Node(node_name));
    cout << dataset.get_column_index_from_name(node_name) << endl;
  }
  REP(i, nodes.size()){
    cout << nodes[i].name << endl;
    vector<Node> except_me;
    REP(j, nodes.size()){
      if(i != j) except_me.push_back(nodes[j]);
    }
    cout << except_me.size() << endl;
    vector<vector<Node>> possible_parents_set = sl.generate_possible_parents_set(except_me, 3);
    cout << "size: " << possible_parents_set.size() << endl; 
    for(vector<Node> parents: possible_parents_set){
      cout << "[";
      for(Node node: parents){
        cout << node.name << ",";
      }
      cout << "]" << endl;
      double local_score = 0;
      local_score = bdeuscore2.get_local_score(nodes[i], parents);
      cout << fixed << setprecision(8) << local_score << endl;
    }
    cout << "----" << endl;
  }

  
}
