#include <bits/stdc++.h>
#include "BayesianNetwork.h"
#include "DataSet.h"
using namespace std;

#ifndef Define_BICScore
#define Define_BICScore

class BICScore{
public:
  BICScore(BayesianNetwork, DataSet);
  BICScore(DataSet);
  double get_score();
  double get_local_score(Node variable, vector<Node>& parents);
private:
  BayesianNetwork model;
  DataSet dataset;

  struct StateCount{
    int parents_candidates_num;
    int child_candidates_num;
    map<vector<int>, pair<int, map<int, int>>> countmap;
    StateCount(int pnum, int cnum, map<vector<int>, pair<int, map<int, int>>> countmap){
      this->parents_candidates_num = pnum;
      this->child_candidates_num = cnum;
      this->countmap = countmap;
    }
  };
  BICScore::StateCount get_state_counts(Node variable, vector<Node>& parents);
};

#endif