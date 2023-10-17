#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
  char symbol = ' ';
  int index = -1;
  int parent = -1;
  vector<int> branches;
};

typedef vector<node> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  string pattern = "";
  int current_node = 0; //index num in trie
  char current_symbol;
  int size = 0; //number of nodes in adjacency list
  node root;
  root.index = 0;
  t.push_back(root);
  bool branch_found = false;
  int branch_index = -1;
  // write your code here
  for (int i = 0; i < patterns.size(); i++) {
    current_node = 0;
    pattern = patterns[i]; 
    for (int j = 0; j < pattern.size(); j++) {
      current_symbol = pattern[j];
      //cout << "current symbol is " << current_symbol << endl;
      if (t[current_node].branches.size() == 0) {
        node newNode;
        size++;
        newNode.index = size;
        newNode.symbol = current_symbol;
        newNode.parent = current_node;
        //cout << "parent of " << newNode.index << " is " << newNode.parent << endl;
        //cout << "added " << newNode.symbol << " at index " << newNode.index << endl;
        t.push_back(newNode);
        t[current_node].branches.push_back(newNode.index);
        current_node = newNode.index;
        //cout << "\tcurrentnode is now " << current_node << endl;
      }
      else {
        for (int k = 0; k < t[current_node].branches.size(); k++) {
          if (t[t[current_node].branches[k]].symbol == current_symbol) {
            branch_found = true;
            branch_index = k;
          }
        }
        if (branch_found) {
          current_node = t[current_node].branches[branch_index];
          //cout << "\t\tmoving down the trie, currentnode is now " << current_node << endl;
        }
        else {
          node newNode;
          size++;
          newNode.index = size;
          newNode.symbol = current_symbol;
          newNode.parent = current_node;
          //cout << "parent of " << newNode.index << " is " << newNode.parent << endl;
          //cout << "added " << newNode.symbol << " at index " << newNode.index << endl;
          t.push_back(newNode);
          t[current_node].branches.push_back(newNode.index);
          current_node = newNode.index;
          //cout << "\tcurrentnode is now " << current_node << endl;
        }
      }
      branch_found = false;
    }
    //cout << "\t\tgoing to next word" << endl;
  }
  return t;
}

int main() {
  size_t n;
  cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  //cout << endl << endl;
  for (size_t i = 0; i < t.size(); ++i) {
    if (t[i].index != 0) {
      cout << t[i].parent << "->" << t[i].index << ":" << t[i].symbol << endl;
    }
  }

  return 0;
}
