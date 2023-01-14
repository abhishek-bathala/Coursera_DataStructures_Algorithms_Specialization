#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
  char symbol = ' ';
  int index = -1;
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
  // write your code here
  for (int i = 0; i < patterns.size(); i++) {
    current_node = 0;
    pattern = patterns[i]; 
    for (int j = 0; j < pattern.size(); j++) {
      current_symbol = pattern[j];
      cout << "current symbol is " << current_symbol << endl;
      if (t[current_node].branches.size() == 0) {
        node newNode;
        size++;
        newNode.index = size;
        newNode.symbol = current_symbol;
        t.push_back(newNode);
        t[current_node].branches.push_back(newNode.index);
        cout << "added " << newNode.symbol << " at index " << newNode.index << endl;
        current_node = newNode.index;
        cout << "\tcurrentnode is now " << current_node << endl;
      }
      else {
        for (int k = 0; k < t[current_node].branches.size(); k++) {
          if (t[t[current_node].branches[k]].symbol == current_symbol) {
            current_node = t[current_node].branches[k];
            cout << "\t\tcurrentnode is now " << current_node << endl;
          }
        }
      }
    }        
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
  cout << endl << endl;
  for (size_t i = 0; i < t.size(); ++i) {
    cout << "i is " << i << " whose symbol is " << t[i].symbol << endl;
    cout << "i has " << t[i].branches.size() << " branches" << endl;
    for (size_t j = 0; j < t[i].branches.size(); j++) {
      cout << i << "->" << j << endl;
    }
  }

  return 0;
}
