#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct edge {
  char symbol = ' ';
  int prev = -1;
  int next = -1;
};

typedef vector<edge> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  string pattern = "";
  int current_node = 0; //index num in trie
  char current_symbol;
  // write your code here
  for (int i = 0; i < patterns.size(); i++) {
    current_node = 0;
    pattern = patterns[i]; 
    for (int j = 0; j < pattern.size(); j++) {
      for (size_t i = 0; i < t.size(); i++) {
        cout << t[i].prev << "->" << t[i].next << ":" << t[i].symbol << "\n";
      }
      cout << endl;

      current_symbol = pattern[j];
      cout << "current symbol is " << current_symbol << endl;
      cout << "current node is " << current_node << endl;
      //finding where new edge goes
      if (t.size() == 0) {
        edge newEdge;
        newEdge.prev = 0;
        newEdge.symbol = current_symbol;
        t.push_back(newEdge);  
      }
      else if (current_symbol == t[current_node].symbol) {

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
  for (size_t i = 0; i < t.size(); ++i) {
      cout << t[i].prev << "->" << t[i].next << ":" << t[i].symbol << "\n";
  }

  return 0;
}
