#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

    vector<vector<int> > edge_existence;

    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
        edges[id ^ 1].capacity += flow;
    }
};

FlowGraph read_data() {
    size_t vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    graph.edge_existence = {vertex_count, vector<int>(vertex_count)};
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            graph.edge_existence[i][j] = 0;
        }
    }


    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        if (u != v) {
            if (graph.edge_existence[u-1][v-1] == 0) {
                //cout << "\nadding new edge between " << u-1 << " and " << v-1 << endl;
                graph.add_edge(u - 1, v - 1, capacity);
                graph.edge_existence[u-1][v-1] = 1;
            }
            else if (graph.edge_existence[u-1][v-1] == 1) {
                //cout << "\nduplicate edge between " << u-1 << " and " << v-1 << endl;
                for (int j = 0; j < graph.graph[u-1].size(); j++) {
                    //cout << "checking " << graph.edges[graph.graph[u-1][j]].capacity << endl;
                    if (graph.edges[graph.graph[u-1][j]].to == v-1) {
                        //cout << "adding " << capacity << " to edge already with " << graph.edges[graph.graph[u-1][j-1]].capacity << " capacity" << endl;
                        graph.edges[graph.graph[u-1][j]].capacity += capacity;
                    }
                }
            }
        }
    }
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    vector<int> parent(graph.size());
    int new_flow;

    for (int a = 0; a < 999; a++) {
        
        // do bfs, find shortest path
        vector<size_t> id_lst;
        vector<int> queue;
        vector<bool> visited;
        vector<int> dist;
        vector<int> prev_dist;
        bool path_exists = false;

        
        for (int i = 0; i < graph.size(); i++) {
            visited.push_back(false);
            dist.push_back(INT_MAX);
            prev_dist.push_back(-1);
        }
        
        visited[from] = true;
        queue.push_back(from);
        dist[from] = 0;

        cout << "bfs" << endl;
        
        while(!queue.empty()) {
            int front = queue.front();
            cout << "front is " << front << endl;
            queue.erase(queue.begin());
            
            cout << "going to visit ";
            for (int i = 0; i < graph.get_ids(front).size(); i++) {
                cout << graph.get_edge(graph.get_ids(front)[i]).to << " ";
            }
            cout << endl;
            

            for (int i = 0; i < graph.get_ids(front).size(); i++) {
                cout << "checking " << graph.get_edge(graph.get_ids(front)[i]).to << " ";
                cout << "whose flow is " << graph.get_edge(graph.get_ids(front)[i]).flow << " and capacity is " << graph.get_edge(graph.get_ids(front)[i]).capacity << endl;
                if ((visited[graph.get_edge(graph.get_ids(front)[i]).to] == false) && (graph.get_edge(graph.get_ids(front)[i]).capacity - graph.get_edge(graph.get_ids(front)[i]).flow != 0) && (graph.get_edge(graph.get_ids(front)[i]).capacity > 0)) {

                    visited[graph.get_edge(graph.get_ids(front)[i]).to] = true;
                    cout << "visited " << graph.get_edge(graph.get_ids(front)[i]).to << endl;
                    dist[graph.get_edge(graph.get_ids(front)[i]).to] = dist[front] + 1;
                    prev_dist[graph.get_edge(graph.get_ids(front)[i]).to] = front;
                    queue.push_back(graph.get_edge(graph.get_ids(front)[i]).to);
                    cout << "queue contains ";
                    for (auto x : queue) {
                        cout << x << " ";
                    }
                    cout << endl;
                    

                    if (graph.get_edge(graph.get_ids(front)[i]).to == to) {
                        cout << "destination found" << endl;
                        path_exists = true;
                        queue.clear();
                        break;
                    }
                }
                else {
                    cout << graph.get_edge(graph.get_ids(front)[i]).to << " already visited " << endl;
                }
            }
        }

        for (auto x : prev_dist) {
        cout << x << ' ';
        }
        cout << endl;
 
        for (auto x : dist) {
            cout << x << ' ';
        }
        cout << endl;

        
        cout << "reversing path" << endl;
        

        int reverse_path = to;
        id_lst.push_back(reverse_path);
        while (prev_dist[reverse_path] != -1) {
            id_lst.push_back(prev_dist[reverse_path]);
            reverse_path = prev_dist[reverse_path];
        }

        reverse(id_lst.begin(), id_lst.end());

        cout << "printing path" << endl;
        for (int i = 0; i < id_lst.size(); i++) {
            cout << id_lst[i] << " ";
        }
        cout << endl;
        
        
        
        //if no path, return 'flow'
        if (id_lst.size() == 1 && id_lst[0] == to) {
            return flow;
        }

        cout << "id_lst is " << endl;
        for (auto x : id_lst) {
            cout << x << " ";
        }
        cout << endl;

        cout << "finding smallest flow" << endl;
        //smallest capacity in shortest path = smallest_flow
        int smallest_flow = INT_MAX;
        for (int i = 0; i < id_lst.size()-1; i++) {
            cout << "adjacent of " << id_lst[i] << " is ";
            for (int a = 0; a < graph.get_ids(id_lst[i]).size(); a++) {
                cout << graph.get_edge(graph.get_ids(id_lst[i])[a]).to << " ";
            }
            cout << endl;

            for (int j = 0; j < graph.get_ids(id_lst[i]).size(); j++) {
                cout << endl << "i: " << i << " j: " << graph.get_edge(graph.get_ids(id_lst[i])[j]).to << endl;
                if (graph.get_edge(graph.get_ids(id_lst[i])[j]).to == id_lst[i+1]) {
                    cout << "checking " << graph.get_edge(graph.get_ids(id_lst[i])[j]).to << " ";
                    cout << "whose flow is " << graph.get_edge(graph.get_ids(id_lst[i])[j]).flow << " and capacity is " << graph.get_edge(graph.get_ids(i)[j]).capacity << endl;
                    if (graph.get_edge(graph.get_ids(id_lst[i])[j]).capacity - graph.get_edge(graph.get_ids(id_lst[i])[j]).flow < smallest_flow && graph.get_edge(graph.get_ids(id_lst[i])[j]).capacity != 0 && graph.get_edge(graph.get_ids(id_lst[i])[j]).capacity - graph.get_edge(graph.get_ids(id_lst[i])[j]).flow != 0) {
                        smallest_flow = graph.get_edge(graph.get_ids(id_lst[i])[j]).capacity - graph.get_edge(graph.get_ids(id_lst[i])[j]).flow;
                        cout << "found smallest flow at " << graph.get_edge(graph.get_ids(i)[j]).to << " ";
                        cout << "whose flow is " << graph.get_edge(graph.get_ids(i)[j]).flow << " and capacity is " << graph.get_edge(graph.get_ids(i)[j]).capacity << endl;
                    } 
                }
            }
        }

        cout << "smallest flow is " << smallest_flow << endl;

        cout << "adding smallest flow" << endl;

        //add smallest_flow to each edge in shortest path
        for (int i = 0; i < id_lst.size()-1; i++) {
            for (int j = 0; j < graph.get_ids(id_lst[i]).size(); j++) {
                cout << "comparing " << id_lst[i] << " and " << graph.get_edge(graph.get_ids(id_lst[i])[j]).to << endl;
                if (graph.get_edge(graph.get_ids(id_lst[i])[j]).to == id_lst[i+1] && graph.get_edge(graph.get_ids(id_lst[i])[j]).capacity != 0) {
                    cout << "adding flow to " << id_lst[i] << ":" << graph.get_edge(graph.get_ids(id_lst[i])[j]).to << endl;
                    graph.add_flow(graph.get_ids(id_lst[i])[j], smallest_flow);
                }
            }
        }

        flow += smallest_flow;

        for (int i = 0; i < graph.edges.size(); i++) {
            cout << "from: " << graph.edges[i].from << " to: " << graph.edges[i].to << " flow: " << graph.edges[i].flow << " cap: " << graph.edges[i].capacity << endl;
        }

        cout << "\tflow is " << flow << endl; 
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
