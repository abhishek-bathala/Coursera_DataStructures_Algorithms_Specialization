#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <float.h>
#include <queue>

using namespace std;

double calculate_distance (int x1, int y1, int x2, int y2) {
  return sqrt( ( (x1-x2) * (x1-x2) ) + ( (y1-y2) * (y1-y2) ) );
  
}

struct Edge {
  double distance;
  int start_index;
  int end_index;

  Edge(double dist, int start, int end) {
    distance = dist;
    start_index = start;
    end_index = end;
  }

  bool operator<(const Edge& edge2) const {
    return distance > edge2.distance;
  }
};

int find_parent (vector<int> &parent, int x) {
  //cout << "\t\t\tfinding parent of " << x << endl;
  if (parent[x] != x) {
    parent[x] = find_parent(parent, parent[x]);
  }
  return parent[x];

}

void union_points (vector<int> &rank, vector<int> &parent, int x, int y) {
  //cout << "\tcreating union between " << x << " " << y << endl;
  int x_parent = find_parent(parent, x);
  int y_parent = find_parent(parent, y);

  if (x_parent == y_parent) {
    return;
  }

  if (rank[x_parent] < rank[y_parent]) {
    parent[x_parent] = y_parent;
  }
  else if (rank[x_parent] > rank[y_parent]) {
    parent[y_parent] = x_parent;
  }
  else {
    parent[y_parent] = x_parent;
    rank[x_parent] = rank[y_parent]+1;
  }

}

double minimum_distance(vector<int> &x, vector<int> &y) {
  double result = 0.;
  //write your code here
  vector<int> parent (x.size());
  vector<int> rank (x.size(), 0);
  priority_queue<Edge> edges;
  vector<int> start;
  vector<int> end;
  vector<pair<int, int>> duplicates;

  for (int i = 0; i < parent.size(); i++) {
    parent[i] = i;
  }

  for (int i = 0; i < x.size(); i++) {
    for (int j = i+1; j < x.size(); j++) {
      Edge new_edge(calculate_distance(x[i], y[i], x[j], y[j]), i, j);
      edges.push(new_edge);
      duplicates.push_back(pair<int, int>(i, j));
      //cout << i << j << " ";
    }
  }

  //cout << endl << edges.size() << endl;
  while (!edges.empty()) {
    Edge temp = edges.top();
    //cout << "temp's distance is now " << temp.distance << " start and end indexes are " << temp.start_index << " " << temp.end_index << " & parent#s are " << parent[temp.start_index] << " " << parent[temp.end_index] << endl;
    if (find_parent(parent, temp.start_index) != find_parent(parent, temp.end_index)) {
      //cout << "\tadding indicies " << temp.start_index << " " << temp.end_index << " whose parent#s are " << parent[temp.start_index] << " " << parent[temp.end_index] << endl;
      result += temp.distance;
      union_points(rank, parent, temp.start_index, temp.end_index);
    }
    edges.pop();
  }

  //cout << endl;
  return result;
} 

int main() {
  size_t n;
  cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  cout << std::setprecision(10) << minimum_distance(x, y) << endl;
}
