#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

#ifndef Define_BayesianNetwork
#define Define_BayesianNetwork

class BayesianNetwork{
public:
  vector<string> column_names;
  
  BayesianNetwork();
  BayesianNetwork(vector<pair<string, string>>&);
  void add_edge(string, string);
  void set_graph(vector<pair<string, string>>& arrowList);
  void show_nodes();
  vector<string> get_node_names();
  vector<Node> get_nodes();
  vector<Node> get_parent_nodes(string);
  vector<Node> get_parent_nodes(Node);
  void save_as_dotscript(string);
private:
  map<string, Node> node_dic;
  void check_graph_structure();
  string to_dot_script();
};

#endif