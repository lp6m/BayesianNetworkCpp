#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

#ifndef Define_StructureLearning
#define Define_StructureLearning

class StructureLearning{
public:
  StructureLearning();
  vector<vector<Node>> generate_possible_parents_set(vector<Node>&, int);
  void test_decompose(BayesianNetwork network);
private:
  struct Decomposed_DAG{
    map<string, int> belong_component_index; //indicates component index which nodes belongs to
    vector<set<Node>> bound_nodes_array;
    vector<set<int>> to_edges; //to_edges[i] contains nodes with directed edge from i-th component
  };
  StructureLearning::Decomposed_DAG decompose_strong_connected_components(BayesianNetwork network);
  void show_decomposed_dag(StructureLearning::Decomposed_DAG);
  string get_nodes_string(set<Node>);
};
#endif