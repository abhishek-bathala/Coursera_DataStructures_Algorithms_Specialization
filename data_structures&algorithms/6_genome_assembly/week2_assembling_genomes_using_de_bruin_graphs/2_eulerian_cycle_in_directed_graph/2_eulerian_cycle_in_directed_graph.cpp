#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

bool has_eulerian_cycle (vector<vector<int> > &adj, vector<int> &incoming) {

    for (int i = 0; i < adj.size(); i++) { 
        //cout << i+1 << " has " << adj[i].size() << " outgoing and " << incoming[i] << " incoming edges" << endl;
        if (adj[i].size() != incoming[i]) { //checking if in-degree == out-degree for all vertices
            return false;
        }
    }

    return true;
}

//hierholzer's algorithm
void find_eulerian_cycle (vector<vector<int> > &adj, vector<int> &path) {
    unordered_map <int, int> edge_count;
    vector<int> temp_path;

    for (int i = 0; i < adj.size(); i++) {
        edge_count[i] = adj[i].size();
    }

    if (!adj.size()) {
        return;
    }

    stack<int> current_path;

    current_path.push(0);
    int current_vertex = 0;

    while (!current_path.empty()) {
        if (edge_count[current_vertex]) {
            current_path.push(current_vertex);
            int next_vertex = adj[current_vertex].back();

            edge_count[current_vertex]--; //used one edge from current_vertex
            adj[current_vertex].pop_back();

            current_vertex = next_vertex;
        }

        else {
            temp_path.push_back(current_vertex);

            current_vertex = current_path.top();
            current_path.pop();
        }
    }

    for (int i = temp_path.size()-1; i >= 0; i--) {
        path.push_back(temp_path[i]);
    }
}

int main() {
    int num_edges, num_vertices;
    cin >> num_vertices >> num_edges;

    vector<vector<int> > adj(num_vertices);
    vector<int> incoming(num_vertices);
    
    //taking input
    for (int i = 0; i < num_edges; i++) {
        int from, to;
        cin >> from >> to;
        from--;
        to--;

        adj[from].push_back(to);
        incoming[to]++;
        //cout << "from " << from+1 << " to " << to+1 << endl;
        //cout << to+1 << ": " << incoming[to] << endl;
    }

    if (!has_eulerian_cycle(adj, incoming)) {
        cout << "0";
        return 0;
    }
    else {
        vector <int> path;
        find_eulerian_cycle(adj, path);
        cout << "1" << endl;
        
        for (int x = 0; x < path.size()-1; x++) {
            cout << path[x]+1;
            if (x != path.size()-2) {
                cout << " ";
            }
        }
        cout << endl;
    }
}