#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void explore(vector<vector<int> > &adj, int i, vector<bool> & used, vector<int> &order) {
  used[i] = true;

  for (int j = 0; j < adj[i].size(); j++) {
    if (!used[adj[i].at(j)]) {
      explore(adj, adj[i].at(j), used, order);
    }
  }
  order.insert(order.begin(), i);
}

void dfs(vector<vector<int> > &adj, vector<bool> &used, vector<int> &order) {
  //write your code here
  for (int i = 0; i < adj.size(); i++) {
    if (used[i] == false) {
      explore(adj, i, used, order);
    }
  }

}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<bool> used(adj.size(), false);
  vector<int> order;
  //write your code here

  dfs(adj, used, order);

  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
