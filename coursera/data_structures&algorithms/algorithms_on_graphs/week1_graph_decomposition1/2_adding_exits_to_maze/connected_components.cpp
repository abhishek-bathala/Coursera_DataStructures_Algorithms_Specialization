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

int number_of_components(vector<vector<int> > &adj, vector<bool> &visited) {
  int res = 0;
  //write your code here

  for (int i = 0; i < adj.size(); i++) {
    if (visited[i] == false) {
      explore(adj, i, visited);
      res++;
      //cout << "res is now " << res << endl;
    }
  }

  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<bool> visited(n, false);
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj, visited);
}
