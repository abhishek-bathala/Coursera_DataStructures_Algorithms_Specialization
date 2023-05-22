#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        /*cout << "3 2" << endl;
        cout << "1 2 0" << endl;
        cout << "-1 -2 0" << endl;
        cout << "1 -2 0" << endl;
        */

        int c = numVertices + (3 * edges.size());
        int v = 3 * numVertices;

        cout << c << " " << v << endl;

        int x = 1;
        for (int i = 0; i < numVertices; i++) {
            cout << x << " " << x+1 << " " << x+2 << " 0" << endl;
            x += 3;
        }

        for (auto edge : edges) {
            cout << -((edge.from - 1) * 3 + 1) << " " << -((edge.to - 1) * 3 + 1) << " 0" << endl;
            cout << -((edge.from - 1) * 3 + 2) << " " << -((edge.to - 1) * 3 + 2) << " 0" << endl;
            cout << -((edge.from - 1) * 3 + 3) << " " << -((edge.to - 1) * 3 + 3) << " 0" << endl;
        }
    }

};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
