#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <limits>
#include <stdlib.h>

using namespace std;

struct TwoSatisfiability {
    struct util {
        util(): index{MIN}, scc{MIN}, id {-1}, on_stack {false}
        {}

        int index, scc, id;
        bool on_stack;
        vector<int> edges;
    };

    TwoSatisfiability(unordered_map<int, util> adj, int numVars): num{ numVars}, g{ move(adj)}, result{ vector<bool> (num, false)}
    {}

    void process_vertex(int x) {
        //cout << "processing " << x << endl;
        auto& vertex = g[x];
        vertex.scc = vertex.index = t++;
        vertex.on_stack = true;
        s.push(x);

        for (auto w : vertex.edges) {
            if (g[w].index == MIN) {
                process_vertex(w);
                vertex.scc = min(vertex.scc, g[w].scc);
            }
            else if (g[w].on_stack) {
                vertex.scc = min(vertex.scc, g[w].index);
            }
        }

        if (vertex.scc == vertex.index) {
            do {
                w = s.top();
                s.pop();

                if (id == g[-w].id) {
                    sat = false;
                    return;
                }

                auto& w_vertex = g[w];
                w_vertex.on_stack = false;
                w_vertex.id = id;

                result[abs(w)-1] = w < 0 ? true : false;
            } while (w != x);
            ++id;
        }
    }

    void solve()
    {
        for (int i = -num; i <= num; ++i) {
            if (g[i].index == MIN && i != 0) {
                process_vertex(i);
            }
        }
    }

    void print_result() const noexcept
    {
        if (!sat) {
            cout << "UNSATISFIABLE" << endl;
            return;
        }

        cout << "SATISFIABLE" << endl;
        for (int i = 0; i < result.size(); i++) {
            cout << (result[i] ? i+1 : -(i+1)) << " ";
        }
        cout << endl;
    }

    int t{0}, id{0}, w{0}, num{0};

    unordered_map<int, util> g;
    vector<bool> result;
    stack<int> s;
    bool sat {true};
    static constexpr int MIN = numeric_limits<int>::min();
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    unordered_map<int, TwoSatisfiability::util> adj(n*2);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[-x].edges.emplace_back(y);
        adj[-y].edges.emplace_back(x);
    }

    TwoSatisfiability find_solution(move(adj), n);
    find_solution.solve();
    find_solution.print_result();



    return 0;
}
