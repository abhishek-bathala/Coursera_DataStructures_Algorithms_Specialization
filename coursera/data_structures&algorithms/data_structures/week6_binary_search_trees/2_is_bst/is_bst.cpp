#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> order;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

class Tree {

public:
  vector<Node> tree;

  bool IsBinarySearchTree() {
    // Implement correct algorithm here
    //cout << "entered isBST" << endl;
    inOrder(tree[0]);
    //cout << "inorder done" << endl;
    for (int i = 0; i < order.size()-1; i++) {
      if (order[i] > order[i+1]) {
        return false;
      }
    }
    return true;
  }


  void inOrder (Node node) {
    //cout << "inorder for " << node.key << " with left and right as " << node.left << " " << node.right << endl;

    if (node.left != -1)
      inOrder(tree[node.left]);
    order.push_back(node.key);
    if (node.right != -1)
    inOrder(tree[node.right]);
  }
};

int main() {
  int nodes;
  cin >> nodes;
  if (nodes == 0) {
    cout << "CORRECT" << endl;
    return 0;
  }
  Tree t;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    t.tree.push_back(Node(key, left, right));
  }
  if (t.IsBinarySearchTree()) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
