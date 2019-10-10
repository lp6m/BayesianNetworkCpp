#include <bits/stdc++.h>

using namespace std;

#ifndef Define_Node
#define Define_Node

class Node{
public:
  string name;
  vector<Node> parents;
  Node();
  Node(string);
  void add_parents(Node);
  bool operator<(const Node &another) const{
      return name < another.name;
  };
};

#endif
