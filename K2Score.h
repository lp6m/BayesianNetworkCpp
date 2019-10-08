#include <bits/stdc++.h>
#include "BayesianNetwork.h"
#include "DataSet.h"
using namespace std;

#ifndef Define_K2Score
#define Define_K2Score

class K2Score{
public:
  K2Score(BayesianNetwork, DataSet);
  K2Score(DataSet);
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
  K2Score::StateCount get_state_counts(Node variable, vector<Node>& parents);
};

#endif