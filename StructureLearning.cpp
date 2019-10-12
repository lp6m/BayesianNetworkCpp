#include <bits/stdc++.h>
#include "BayesianNetwork.h"
#include "Node.h"
#include "StructureLearning.h"
#include "Util.h"

using namespace std;

StructureLearning::StructureLearning(){

}

vector<vector<Node>> StructureLearning::generate_possible_parents_set(vector<Node>& nodes, int max_parent_num){
  vector<vector<Node>> candidates;
  //push empty vector which means no parent case(k=0)
  candidates.push_back(vector<Node>());

  FOR(k, 1, max_parent_num+1){
    //generate nCk
    int n = nodes.size();
    queue<pair<int, vector<int>>> q; //pos, array
    REP(i, n-k+1){
      vector<int> tmp(k);
      tmp[0] = i;
      q.push(make_pair(1, tmp));
    } 
    while(!q.empty()){
      auto front = q.front();
      q.pop();
      int pos = front.first;
      vector<int> array = front.second;

      if(pos == k){
        //combination complete
        vector<Node> newcomb;
        REP(i, k){
          newcomb.push_back(nodes[array[i]]);
        }
        candidates.push_back(newcomb);
      }else{
        int old = array[pos-1];
        FOR(i, old+1, n-k+pos+1){
          array[pos] = i;
          q.push(make_pair(pos+1, array));
        }
      }
    }
  }
  return candidates;
}

string StructureLearning::get_nodes_string(set<Node> node_set){
  string res = "{";
  int size = node_set.size();
  int cnt = 0;
  for(auto itr = node_set.begin(); itr != node_set.end(); itr++){
    Node node = *itr;
    res += node.name;
    if(cnt != size - 1) res += ", ";
    cnt++;
  }
  res += "}";
  return res;
}

vector<int> StructureLearning::topological_sort(StructureLearning::Decomposed_DAG d_DAG){
  vector<int> sorted_nodes_indices;
  queue<int> q;
  int node_num = d_DAG.from_edges.size();
  REP(i, node_num){
    if(d_DAG.from_edges[i].size() == 0) q.push(i);
  }
  while(!q.empty()){
    int node_index = q.front();
    q.pop();
    sorted_nodes_indices.push_back(node_index);
    int to_node_num = d_DAG.to_edges[node_index].size();
    REP(j, to_node_num){
      int to_node_index = *(d_DAG.to_edges[node_index].begin());//get the value of first iterator //any index is OK
      d_DAG.to_edges[node_index].erase(to_node_index);
      d_DAG.from_edges[to_node_index].erase(node_index);
      if(d_DAG.from_edges[to_node_index].size() == 0) q.push(to_node_index);
    }
  }

  //DAG check
  REP(i, node_num){
    if(d_DAG.from_edges[i].size() != 0){
      throw "given graph was not DAG. Topological Sort failed.";
    }
  }

  return sorted_nodes_indices;
}

void StructureLearning::show_decomposed_dag(StructureLearning::Decomposed_DAG& decomposed_DAG, vector<int>& sorted_nodes_indices){
  map<int, string> cache_set_node_string;

  REP(i, decomposed_DAG.bound_nodes_array.size()){
    // int parent_index = sorted_nodes_indices[i];
    int parent_index = i;
    set<Node> parent_nodes = decomposed_DAG.bound_nodes_array[parent_index];
    string parent_string;
    if(cache_set_node_string.count(parent_index) != 0) parent_string = cache_set_node_string[parent_index];
    else {
      parent_string = get_nodes_string(parent_nodes);
      cache_set_node_string[parent_index] = parent_string;
    }

    set<int> child_indices = decomposed_DAG.to_edges[parent_index];
    for(auto itr = child_indices.begin(); itr != child_indices.end(); itr++){
      int child_index = *itr;
      set<Node> child_nodes = decomposed_DAG.bound_nodes_array[child_index];
      string child_string;
      if(cache_set_node_string.count(child_index) != 0) child_string = cache_set_node_string[child_index];
      else {
        child_string = get_nodes_string(child_nodes);
        cache_set_node_string[child_index] = child_string;
      }
      cout << parent_string << " -> " << child_string << endl;
    }
  }

  cout << "--------" << endl;

}

struct StackedOrderNodes{
  vector<Node> stacked_order_nodes;
  map<string, bool> is_reached;
  void dfs(Node node, map<string, vector<Node>>& children_map){
    if(is_reached[node.name]) return;
    is_reached[node.name] = true;
    for(Node to: children_map[node.name]) dfs(to, children_map);
    stacked_order_nodes.push_back(node);
  }
  void do_dfs(vector<Node>& nodes, map<string, vector<Node>>& children_map){
    for(Node node: nodes) dfs(node, children_map);
  }
};

StructureLearning::Decomposed_DAG StructureLearning::decompose_strong_connected_components(BayesianNetwork network){
  //TODO: some algorithms does not need to make reverse network. I will implement in the future for optimization.
  Decomposed_DAG decomposed_DAG;

  //variable for network information collection
  vector<Node> nodes = network.get_nodes();
  map<string, vector<Node>> children_map;
  map<pair<string, string>, bool> is_edge_used2; //use for the second DFS in reversed network
  map<string, bool> is_bound; //use for the second DFS

  //collect all edges, create network whose edge is reversed
  for(Node& node: nodes){
    is_bound[node.name] = false;
    vector<Node> parents = node.parents;
    for(Node& parent: parents){
      is_edge_used2[make_pair(node.name, parent.name)] = false;
      children_map[parent.name].push_back(node);
    }
  }

  //first DFS
  StackedOrderNodes son;
  son.do_dfs(nodes, children_map);
  vector<Node> stacked_order_nodes = son.stacked_order_nodes;

  reverse(stacked_order_nodes.begin(), stacked_order_nodes.end());

  //second DFS
  int components_cnt = 0;
  for(Node& node: stacked_order_nodes){
    if(is_bound[node.name]) continue;
    set<Node> bound_nodes = {node};
    decomposed_DAG.belong_component_index[node.name] = components_cnt;
    is_bound[node.name] = true;
    stack<Node> st2;
    st2.push(node);

    while(!st2.empty()){
      Node now_node = st2.top();
      st2.pop();
      is_bound[now_node.name] = true;
      vector<Node> to_nodes = network.get_parent_nodes(now_node.name);//parents of original network is destinations of reversed network
      for(Node& to_node: to_nodes){
        if(is_bound[to_node.name] == false){
          is_edge_used2[make_pair(now_node.name, to_node.name)] = true;
          st2.push(to_node);
          decomposed_DAG.belong_component_index[to_node.name] = components_cnt;
          bound_nodes.insert(to_node);
        }
      }
      is_bound[now_node.name] = true;
    }
    if(bound_nodes.size() > 0){
      components_cnt++;
      decomposed_DAG.bound_nodes_array.push_back(bound_nodes);
    }
  }
  
  //reserve edge vector array with number of components
  REP(i, decomposed_DAG.bound_nodes_array.size()){
    decomposed_DAG.to_edges.push_back(set<int>());
    decomposed_DAG.from_edges.push_back(set<int>());
  }

  //check unused edge which means edge of DAG
  for(auto itr = is_edge_used2.begin(); itr != is_edge_used2.end(); itr++){
    if(itr->second == false){
      pair<string, string> edge = itr->first;
      string from_name = edge.first;
      string to_name = edge.second;
      int from_index = decomposed_DAG.belong_component_index[from_name];
      int to_index = decomposed_DAG.belong_component_index[to_name];
      if(from_index == to_index) continue;
      swap(from_index, to_index); //change to original direction by reverse
      decomposed_DAG.to_edges[from_index].insert(to_index);
      decomposed_DAG.from_edges[to_index].insert(from_index);
    }
  }
  return decomposed_DAG;
}

void StructureLearning::test_decompose(BayesianNetwork network){
  auto dag = decompose_strong_connected_components(network);
  vector<int> sorted_nodes_indices = topological_sort(dag);
  show_decomposed_dag(dag, sorted_nodes_indices); 
}