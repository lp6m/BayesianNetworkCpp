#include <bits/stdc++.h>
#include "Util.h"
#include "StructureLearning.h"
#include "Node.h"

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