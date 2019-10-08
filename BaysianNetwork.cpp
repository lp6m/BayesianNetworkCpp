#include <bits/stdc++.h>
#include "BdeuScore.h"
#include "Node.h"
#include "Column.h"

using namespace std;


BayesianNetwork::BayesianNetwork(){

}

BayesianNetwork::BayesianNetwork(vector<pair<string, string>> arrowList){
  set_graph(arrowList);
}

void BayesianNetwork::set_graph(vector<pair<string, string>> edgeList){
  for(auto edge :edgeList){
    this->add_edge(edge.first, edge.second);
  }
}

void BayesianNetwork::add_edge(string from_name, string to_name){
  if(this->node_dic.count(from_name) == 0) this->node_dic[from_name] = Node(from_name);
  if(this->node_dic.count(to_name) == 0) this->node_dic[to_name] = Node(to_name);

  this->node_dic[to_name].add_parents(this->node_dic[from_name]);
}

void BayesianNetwork::check_graph_structure(){
  //TODO
}

void BayesianNetwork::show_nodes(){
  for(auto itr = this->node_dic.begin(); itr != this->node_dic.end(); itr++){
    cout << itr->first << ", ";
  }
  cout << endl;
}

vector<string> BayesianNetwork::get_node_names(){
  vector<string> names;
  for(auto itr = this->node_dic.begin(); itr != this->node_dic.end(); itr++){
    names.push_back(itr->first);
  }
  return names;
}

vector<Node> BayesianNetwork::get_nodes(){
  vector<Node> nodes;
  for(auto itr = this->node_dic.begin(); itr != this->node_dic.end(); itr++){
    nodes.push_back(itr->second);
  }
  return nodes;
}

vector<Node> BayesianNetwork::get_parent_nodes(Node child_node){
  return child_node.parents;
}

vector<Node> BayesianNetwork::get_parent_nodes(string child_name){
  if(this->node_dic.count(child_name) == 0) throw "Exception: network does not have specified child node: " + child_name;
  Node node = this->node_dic[child_name];
  return BayesianNetwork::get_parent_nodes(node);
}

string BayesianNetwork::to_dot_script(){
  //convert network structure to DOT script for graphviz
  string s = "digraph{\n";
  for(auto itr = this->node_dic.begin(); itr != this->node_dic.end(); itr++){
    Node node = itr->second;
    for(Node parent: node.parents){
      s += "  " + parent.name + " -> " + node.name + "\n"; 
    }
  }
  s += "}\n";
  return s;
}

void BayesianNetwork::save_as_dotscript(string filename){
  ofstream outputfile(filename);
  outputfile << this->to_dot_script();
  outputfile.close();
}
