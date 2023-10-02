#include <bits/stdc++.h>
using namespace std;

struct ConvertHampathToSat {
    int numVertices;
    vector<vector<bool> > adjacencyMatrix;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        adjacencyMatrix(n, vector<bool> (n, false))
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
        string result = "";
        int numOfClauses = 0;
        int numOfVariables = numVertices*numVertices;
        int temp = 1;
        vector<vector<int> > vertexLabels (numVertices, vector<int> (numVertices, 0));

        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                vertexLabels[i][j] = temp++;
            }
        }

        //each vertex is in path
        for (int i = 0; i < numVertices; i++) {
            numOfClauses++;
            for (int j = 0; j < numVertices; j++) {
                result += to_string(vertexLabels[i][j]) + " ";
            }
            result += "0\n";
        }


        //each vertex appears only once in path
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                for (int k = i + 1; k < numVertices; k++) {
                    numOfClauses++;
                    result += to_string(-vertexLabels[i][j]) + " " + to_string(-vertexLabels[k][j]) + " 0\n";
                }
            }
        }

        //each position of path has a vertex
        for (int i = 0; i < numVertices; i++) {
            numOfClauses++;
            for (int j = 0; j < numVertices; j++) {
                result += to_string(vertexLabels[j][i]) + " ";
            }
            result += "0\n";
        }


        //only 1 vertex is in each position of path
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                for (int k = j + 1; k < numVertices; k++) {
                    numOfClauses++;
                    result += to_string(-vertexLabels[i][j]) + " " + to_string(-vertexLabels[i][k]) + " 0\n";
                }
            }
        }


        //two consecutive vertices in path have an edge between them
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (i != j && !adjacencyMatrix[i][j]) {
                    for (int k = 0; k < numVertices - 1; k++) {
                        numOfClauses++;
                        result += to_string(-vertexLabels[i][k]) + " " + to_string(-vertexLabels[j][k+1]) + " 0\n";
                    }
                }
            }
        }



        cout << numOfClauses << " " << numOfVariables << endl << result << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);

    int from, to;
    for (int i = 0; i < m; ++i) {
        cin >> from >> to;
        from--;
        to--;
        converter.adjacencyMatrix[from][to] = true;
        converter.adjacencyMatrix[to][from] = true;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
