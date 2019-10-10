#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

Node::Node(){}
Node::Node(string m_name): name(m_name){
}

void Node::add_parents(Node node){
  this->parents.push_back(node);
}

