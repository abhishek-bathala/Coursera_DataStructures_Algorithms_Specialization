#include <iostream>
#include <vector>

using namespace std;
vector<int> order;

void explore(vector<vector<int> > &adj, int i, vector<int> &visited, bool &cyclic) {
  if (visited[i] == 0) {
    visited[i] = -1;
  }
  if (cyclic) {
    return;
  }
  //cout << "visited " << i+1 << " with value -1 " << endl;

  //cout << "explored " << i+1 << endl;
  for (int j = 0; j < adj[i].size(); j++) {
    if (visited[adj[i].at(j)] == 0) {
      //cout << "going to " << adj[i].at(j)+1 << endl;
      explore(adj, adj[i].at(j), visited, cyclic);
    }
    //cout << "visited of " << adj[i].at(j)+1 << " is now " << visited[adj[i].at(j)] << endl;
    if (visited[adj[i].at(j)] == -1) {
      cyclic = true;
      //cout << "   cyclic is true at node " << i+1 << endl;
    }
  }
  order.push_back(i);
  visited[i] = 1;
  //cout << "completed visiting " << i+1 << " whose value is " << visited[i] << endl;
}

int acyclic(vector<vector<int> > &adj, vector<int> &visited) {
  //write your code here
  int a = 1;
  bool cyclic = false;
  for (int i = 0; i < adj.size(); i++) {
    if (visited[i] == false) {
      explore(adj, i, visited, cyclic);
    }
  }

  /*for (int i = 0; i < order.size(); i++) {
    cout << order[i]+1 << " ";
  }
  cout << endl;*/

  if (cyclic) {
    return 1;
  }
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  
  //0 means node has not been visited, -1 means it has been visited and children
  //are being visited, 1 means node and its children have all been visited
  vector<int> visited(n, 0);

  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  cout << acyclic(adj, visited);
}
