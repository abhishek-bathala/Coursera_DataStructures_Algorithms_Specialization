#include <iostream>
#include <vector>

using namespace std;

//bellman-ford algorithm
long negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  vector<long> dist (adj.size(), INT8_MAX);
  int v = adj.size();

  //adding dummy node with edges of weight 0 to gain access to all pre-existing nodes
  adj.push_back(vector<int>());
  cost.push_back(vector<int>());
  for (int i = 0; i < v-1; i++) {
    adj[adj.size()-1].push_back(i);
    cost[adj.size()-1].push_back(0);
  }
  dist[v-1] = 0;

  //cout << "added extra node connected to all other nodes" << endl;
  v = adj.size();

  //relaxing all edges in graph v-1 times
  for (int a = 0; a < v-1; a++) {
    for (int i = 0; i < v; i++) {
      for (int j = 0; j < adj[i].size(); j++) {
        if (dist[adj[i].at(j)] > dist[i] + cost[i].at(j)) {
          dist[adj[i].at(j)] = dist[i] + cost[i].at(j);
        }
      }
    }
    /*cout << "for each node, dist is " << endl;
    for (int i = 0; i < dist.size(); i++) {
      cout << i+1 << " " << dist[i] << endl;
    }
    cout << endl;*/
  }

  
  //trying to relax all edges in graph again, if edges can be re-relaxed, return as there is a cycle
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < adj[i].size(); j++) {
      if (dist[adj[i].at(j)] > dist[i] + cost[i].at(j)) {
        return 1;
        //dist[adj[i].at(j)] = dist[i] + cost[i].at(j);
      }
    }
  }

  return 0;
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
  cout << negative_cycle(adj, cost);
}
