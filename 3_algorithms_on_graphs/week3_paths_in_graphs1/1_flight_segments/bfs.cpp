#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  vector<int> distances (adj.size(), INT8_MAX);
  vector<int> queue;
  int index = -1;

  distances[s] = 0;
  queue.push_back(s);

  //BFS
  while (!queue.empty()) {
    index = queue[0];
    queue.erase(queue.begin());
    for (int i = 0; i < adj[index].size(); i++) {
      if (distances[adj[index].at(i)] == INT8_MAX) {
        queue.push_back(adj[index].at(i));
        distances[adj[index].at(i)] = distances[index]+1;
      }
    }
  }

  if (distances[t] == INT8_MAX) {
    return -1;
  }
  return distances[t];
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, s, t);
}
