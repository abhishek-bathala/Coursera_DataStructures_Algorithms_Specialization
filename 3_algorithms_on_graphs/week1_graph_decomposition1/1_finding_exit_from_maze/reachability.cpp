#include <iostream>
#include <vector>

using namespace std;

void explore(vector<vector<int> > &adj, int i, vector<bool> &visited) {
  //cout << "visited " << i << endl;
  visited[i] = true;
  for (int j = 0; j < adj[i].size(); j++) {
    if (!visited[adj[i].at(j)]) {
      explore(adj, adj[i].at(j), visited);
    }
  }
}

int reach(vector<vector<int> > &adj, int x, int y, vector<bool> &visited) {
  //write your code here
  explore(adj, x, visited);

  if (visited[x] == true && visited[y] == true) {
    return 1;
  }
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<bool> visited(n, false);
  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  cin >> x >> y;
  cout << reach(adj, x - 1, y - 1, visited);
}
