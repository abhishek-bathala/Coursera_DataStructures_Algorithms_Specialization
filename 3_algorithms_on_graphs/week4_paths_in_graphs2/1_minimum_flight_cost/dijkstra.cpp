#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code here
  priority_queue<int, vector<int>, greater<int> > q;
  vector<long> previous(adj.size(), -1);
  vector<long> dist (adj.size(), INT32_MAX); 
  int index = -1;

  dist[s] = 0;
  q.push(s);

  while (!q.empty()) {
    index = q.top();
    q.pop();
    //cout << "popped " << index+1 << endl;

    for (int i = 0; i < adj[index].size(); i++) {
      if (dist[adj[index].at(i)] > (dist[index] + cost[index].at(i))) {
        dist[adj[index].at(i)] = (dist[index] + cost[index].at(i));
        previous[adj[index].at(i)] = index;
        q.push(adj[index].at(i));
        //cout << "pushing " << index+1 << " to queue" << endl;
        
      }
    }
  }

  if (dist[t] == INT32_MAX) {
    return -1;
  }
  return dist[t];
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, cost, s, t);
}
