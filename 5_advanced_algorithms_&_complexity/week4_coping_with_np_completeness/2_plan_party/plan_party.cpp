#include <iostream>
#include <vector>
//#include <sys/resource.h>

using namespace std;

struct Vertex {
    int weight;
    vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i) {
        cin >> tree[i].weight;
    }

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

/*void dfs(const Graph &tree, int vertex, int parent) {
    cout << "going to " << vertex << endl;
    on_stack[vertex] = true;
    for (int child : tree[vertex].children) {
        if (child != parent && !on_stack[child]) {
            dfs(tree, child, vertex);
        }
    }

    on_stack[vertex] = false;

    // This is a template function for processing a tree using depth-first search.
    // Write your code here.
    // You may need to add more parameters to this function for child processing.
}*/

int funParty(int current, const Graph &tree, int parent, Sum& subtree_sum) {
    //cout << endl << "visited " << current << " is onstack" << endl;
    

    if (subtree_sum[current] == -1) {
        if (tree[current].children.size() == 0) {
            //cout << "found leaf at " << current << endl;
            subtree_sum[current] = tree[current].weight;

        }
        else {
            //cout << current << " is not a leaf" << endl;
            int m1 = tree[current].weight;
            for (int i = 0; i < tree[current].children.size(); i++) {
                int x = tree[current].children[i];
                if (x != parent) {
                    for (int j = 0; j < tree[x].children.size(); j++) {
                        if (tree[x].children[j] != current)
                            m1 += funParty(tree[x].children[j], tree, x, subtree_sum);
                    }
                }
            }
            int m0 = 0;

            for (int i = 0; i < tree[current].children.size(); i++) {
                if (tree[current].children[i] != parent)
                    m0 += funParty(tree[current].children[i], tree, current, subtree_sum);
            }

            subtree_sum[current] = max(m0, m1);
        }
    }

    return subtree_sum[current];
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    
    // You must decide what to return.

    /*for (int i = 0; i < tree.size(); i++) {
        cout << "index " << i << ": weight is " << tree[i].weight << " children are ";
        for (int j = 0; j < tree[i].children.size(); j++) {
            cout << tree[i].children[j] << " ";
        }
        cout << endl;
    }
    */

    Sum subtree_sum;
    subtree_sum.assign(size, -1);


    return funParty(0, tree, -1, subtree_sum);
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    /*const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
    */

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    cout << weight << endl;
    return 0;
}
