#include <bits/stdc++.h>
#include "BdeuScore.h"
#include "BayesianNetwork.h"
using namespace std;

BdeuScore::BdeuScore(BayesianNetwork _model, DataSet _dataset): model(_model), dataset(_dataset){

}

BdeuScore::BdeuScore(DataSet _dataset): dataset(_dataset){

}

double BdeuScore::get_score(){
  double score = 0;
  auto nodes = this->model.get_nodes();
  for(Node node: nodes){
    score += this->get_local_score(node, node.parents);
  }
  return score;
}

double BdeuScore::get_local_score(Node variable, vector<Node>& parents){
  const double ess = 10.0;//equivalent_sample_size default value refers to pgmpy implementation
  double local_score = 0;
  StateCount statecount = this->get_state_counts(variable, parents);
  double nik_prime = (double)ess/(double)statecount.parents_candidates_num;
  double nijk_prime = nik_prime/(double)statecount.child_candidates_num;
  //does not iterate all combinations. only iterate in existing combinations
  for(auto pitr = statecount.countmap.begin(); pitr != statecount.countmap.end(); pitr++){
    double nik = (double)(pitr->second.first);
    auto childmap = pitr->second.second;
    if(nik > 0) local_score += lgamma(nik_prime) - lgamma(nik + nik_prime);
    for(auto citr = childmap.begin(); citr != childmap.end(); citr++){
      double nijk = (double)(citr->second);
      if(nijk > 0) local_score += lgamma(nijk_prime + nijk) - lgamma(nijk_prime);
    }
  }
  return local_score;
}

BdeuScore::StateCount BdeuScore::get_state_counts(Node variable, vector<Node>& parents){
  DataSet dataset = this->dataset;
  if(parents.size() > 0){
    int parents_candidates_num = 1;

    vector<int> parent_indices;
    for(Node parent_node: parents){
      string parent_name = parent_node.name;
      int column_index = dataset.get_column_index_from_name(parent_name);
      parent_indices.push_back(column_index);
      parents_candidates_num *= dataset.columns[column_index].get_kind_num();
    }

    int child_column_index = dataset.get_column_index_from_name(variable.name);
    int child_candidates_num = dataset.columns[child_column_index].get_kind_num();
    map<vector<int>, pair<int, map<int, int>>> family_states_countmap;

    for(vector<int> oneline: dataset.data){
      vector<int> ar;
      for(int index: parent_indices){
        ar.push_back(oneline[index]);
      }
      if(family_states_countmap.count(ar) == 0){
        map<int,int> m;
        family_states_countmap[ar] = make_pair(0, m);
      } 
      family_states_countmap[ar].first++;

      int child_val = oneline[child_column_index];
      if(family_states_countmap[ar].second.count(child_val) == 0){
        family_states_countmap[ar].second[child_val] = 0;
      }
      family_states_countmap[ar].second[child_val]++;
    }
    return BdeuScore::StateCount(parents_candidates_num, child_candidates_num, family_states_countmap);

  }else{
    //leaf = no parent
    int child_column_index = dataset.get_column_index_from_name(variable.name);
    int child_candidates_num = dataset.columns[child_column_index].get_kind_num();
    map<int,int> child_countmap;
    for(vector<int> oneline: dataset.data){
      int val = oneline[child_column_index];
      if(child_countmap.count(val) == 0) child_countmap[val] = 0;
      child_countmap[val]++;
    }
    vector<int> dummy_parent = vector<int>(1);
    map<vector<int>, pair<int, map<int, int>>> states_countmap;
    states_countmap[dummy_parent] = make_pair(dataset.data.size(), child_countmap);
    return BdeuScore::StateCount(1, child_candidates_num, states_countmap);
  }
}
