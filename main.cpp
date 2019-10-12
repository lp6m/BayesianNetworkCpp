#include <bits/stdc++.h>
#include "Node.h"
#include "BayesianNetwork.h"
#include "BdeuScore.h"
#include "BICScore.h"
#include "K2Score.h"
#include "Column.h"
#include "StructureLearning.h"
#include "DataSet.h"
#include "Util.h"

using namespace std;

void scoretest(){
  vector<pair<string, string>> vp;
  vp.push_back(make_pair("A", "B"));
  vp.push_back(make_pair("B", "C"));
  vp.push_back(make_pair("D", "B"));
  vp.push_back(make_pair("C", "E"));
  vp.push_back(make_pair("B", "F"));
  vp.push_back(make_pair("C", "G"));
  vp.push_back(make_pair("B", "G"));
  BayesianNetwork bn(vp);
  DataSet dataset;
  vector<string> columns = {"A", "B", "C", "D", "E", "F", "G"};
  vector<vector<int>> data = {
    {1, 1, 0, 1, 0, 0, 0},
    {0, 2, 1, 1, 1, 1, 1},
    {2, 1, 0, 0, 2, 0, 1},
    {1, 1, 0, 1, 1, 1, 0},
    {1, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0},
    {0, 2, 1, 1, 2, 1, 1},
    {1, 0, 1, 1, 1, 1, 1},
    {1, 1, 2, 1, 0, 1, 0},
    {1, 2, 0, 1, 0, 1, 2}
  };
  dataset.set_data(columns, data);
  BdeuScore bdeuscore(bn, dataset);
  K2Score k2score(bn, dataset);
  BICScore bicscore(bn, dataset);
  cout << fixed << setprecision(8) << "BdeuScore: " << bdeuscore.get_score() << endl;
  cout << fixed << setprecision(8) << "K2Score: " << k2score.get_score() << endl;
  cout << fixed << setprecision(8) << "BICScore: " << bicscore.get_score() << endl;
}

void decompose_test(){
  vector<pair<string, string>> vp;
  // vp.push_back(make_pair("A", "B"));
  // vp.push_back(make_pair("B", "C"));
  // vp.push_back(make_pair("C", "D"));
  // vp.push_back(make_pair("C", "E"));
  // vp.push_back(make_pair("E", "C"));
  // vp.push_back(make_pair("E", "G"));
  // vp.push_back(make_pair("E", "H"));
  // vp.push_back(make_pair("H", "I"));
  // vp.push_back(make_pair("H", "J"));
  // vp.push_back(make_pair("G", "F"));
  // vp.push_back(make_pair("F", "G"));
  // vp.push_back(make_pair("D", "G"));
  // vp.push_back(make_pair("D", "K"));
  // vp.push_back(make_pair("D", "L"));
  // vp.push_back(make_pair("L", "M"));

  vp.push_back(make_pair("T", "A"));
  vp.push_back(make_pair("T", "L"));
  vp.push_back(make_pair("L", "T"));
  vp.push_back(make_pair("T", "E"));
  vp.push_back(make_pair("E", "T"));
  vp.push_back(make_pair("L", "E"));
  vp.push_back(make_pair("E", "L"));
  vp.push_back(make_pair("L", "S"));
  vp.push_back(make_pair("S", "B"));
  vp.push_back(make_pair("B", "S"));
  vp.push_back(make_pair("E", "X"));
  vp.push_back(make_pair("B", "D"));
  vp.push_back(make_pair("D", "B"));
  vp.push_back(make_pair("E", "D"));

  BayesianNetwork bn(vp);
  StructureLearning sl;
  sl.test_decompose(bn);
}

int main(){
  // decompose_test();
  // return 0;
  StructureLearning sl;
  DataSet dataset;
  dataset.set_data_fromfile("dataset/asia10K.csv");
  cout << "DataSet score load end" << endl;
  BdeuScore bdeuscore(dataset);
  // K2Score k2score(dataset);
  // BICScore bicscore(dataset);

  vector<Node> nodes;
  vector<string> node_names = {"S", "L", "A", "T", "E", "X", "B", "D"};
  for(string node_name: node_names){
    nodes.push_back(Node(node_name));
    cout << dataset.get_column_index_from_name(node_name) << endl;
  }
  BayesianNetwork bn;
  vector<pair<pair<vector<Node>, Node>, double>> res;

  REP(i, nodes.size()){
    double max_local_score = -1e15;
    vector<Node> max_parents_set;

    cout << nodes[i].name << endl;
    vector<Node> except_me;
    REP(j, nodes.size()){
      if(i != j) except_me.push_back(nodes[j]);
    }
    cout << except_me.size() << endl;
    vector<vector<Node>> possible_parents_set = sl.generate_possible_parents_set(except_me, 2);
    cout << "size: " << possible_parents_set.size() << endl; 
    for(vector<Node> parents: possible_parents_set){
      cout << "[";
      for(Node node: parents){
        cout << node.name << ",";
      }
      cout << "]" << endl;
      double local_score = 0;
      local_score = bdeuscore.get_local_score(nodes[i], parents);
      // local_score = k2score.get_local_score(nodes[i], parents);
      // local_score = bicscore.get_local_score(nodes[i], parents);
      cout << fixed << setprecision(8) << local_score << endl;
      if(local_score > max_local_score){
        max_local_score = local_score;
        max_parents_set = parents;
      }
    }
    res.push_back(make_pair(make_pair(max_parents_set, nodes[i].name), max_local_score));
    cout << "----" << endl;
  }
  for(int i = 0; i < res.size(); i++){
    Node node = res[i].first.second;
    vector<Node> parents = res[i].first.first;
    double max_local_score = res[i].second;
     //add edge of family which has maximum local score
    for(Node parentnode: parents){
      bn.add_edge(parentnode.name, node.name);  
    }
    cout << fixed << setprecision(8) << max_local_score << " : [";
    REP(j, parents.size()) cout << parents[j].name << ", ";
    cout << "] ->" << node.name << endl;
  }


  bn.save_as_dotscript("data_from_R_Bdeu.dot");
  
  StructureLearning sl2;
  sl2.test_decompose(bn);
}
