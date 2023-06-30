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
        int from, to, capacity, flow, lower_bound;
    };

    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

    vector<int> in, out;

    int lower_bound_sum = 0;

    size_t last_edge;

    explicit FlowGraph(size_t n, size_t m, size_t last_edge): graph(n), last_edge{last_edge} {
        edges.reserve(m*2);
    }

    void add_edge(int from, int to, int capacity, int lower_bound) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0, lower_bound};
        Edge backward_edge = {to, from, 0, 0, lower_bound};
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
    }
};

FlowGraph read_data() {
    size_t vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    int initial_edge_count = edge_count;
    edge_count += vertex_count*2;
    vertex_count += 2;
    FlowGraph graph(vertex_count, edge_count, initial_edge_count*2);
    vector<int> temp_out(vertex_count);
    vector<int> temp_in(vertex_count);

    for (int i = 0; i < initial_edge_count; ++i) {
        int u, v, lower_bound, capacity;
        cin >> u >> v >> lower_bound >> capacity;
        graph.add_edge(u, v, capacity - lower_bound, lower_bound);
        temp_out[u] += lower_bound;
        temp_in[v] += lower_bound;
        graph.lower_bound_sum += lower_bound;
    }

    for (int i = 1; i < vertex_count-1; i++) {
        graph.add_edge(0, i, temp_in[i], temp_in[i]);
        graph.add_edge(i, vertex_count-1, temp_out[i], temp_out[i]);
    }

    graph.out = temp_out;
    graph.in = temp_in;
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    /* your code goes here */
    vector<int> parent(graph.size());
    int flow = 0;

    do {
        // do bfs, find shortest path
        vector<int> queue;
        queue.push_back(from);
        fill(parent.begin(), parent.end(), -1);

        while (!queue.empty()) {
            int front = queue.front();
            queue.erase(queue.begin());

            for (auto x : graph.get_ids(front)) {
                FlowGraph::Edge edge = graph.get_edge(x);

                if (parent[edge.to] == -1 && edge.capacity > edge.flow && edge.to != from) {
                    parent[edge.to] = x;
                    queue.push_back(edge.to);
                }
            }
        }

        //travese path from bfs
        if (parent[to] != -1) {
            int smallest_flow = INT_MAX;

            //find smallest flow in path
            for (int i = parent[to]; i != -1; i = parent[graph.get_edge(i).from]) {
                smallest_flow = min(smallest_flow, graph.get_edge(i).capacity - graph.get_edge(i).flow);

            }

            //add smallest flow to nodes in path
            for (int i = parent[to]; i != -1; i = parent[graph.get_edge(i).from]) { 
                graph.add_flow(i, smallest_flow);
            }

            flow += smallest_flow;
        }

        
    } while (parent[to] != -1);

    return flow;
}


int main() {
    ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();
    //cout << "lowerboundsum is " << graph.lower_bound_sum << endl;

    if (max_flow(graph, 0, graph.size() -1 ) == graph.lower_bound_sum) {
        cout << "YES" << endl;

        for (size_t i = 0; i < graph.last_edge; i += 2) {
            cout << graph.edges[i].flow + graph.edges[i].lower_bound << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }


    return 0;
}
