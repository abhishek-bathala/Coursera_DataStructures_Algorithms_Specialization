#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int key;
  int left;
  int right;
  int index;

  Node() : key(0), left(-1), right(-1), index(-1) {}
  Node(int key_, int left_, int right_, int index_) : key(key_), left(left_), right(right_), index(index_) {}
};

vector<Node> nodes;

class Tree {
public:
  vector<Node> tree;

  bool IsBinarySearchTree() {
    // Implement correct algorithm here
    //cout << "entered isBST" << endl;
    inOrder(tree[0]);
    //cout << "inorder done" << endl;
    /*for (int i = 0; i < nodes.size(); i++) {
      cout << nodes[i].key << " ";
    }*/
    //cout << endl;
    for (int i = 0; i < nodes.size()-1; i++) {
      if (nodes[i].key > nodes[i+1].key) {
        return false;
      }
      if (nodes[i].key == nodes[i+1].key) {
        //cout << "Have same key: " << order[i] << " " << order[i+1] << endl;
        //cout << "at indicies " << nodes[i].index << " " << nodes[i+1].index << endl;
        if (nodes[i].index > nodes[i+1].index) {
          return false;
        }
      }
    }
    return true;
  }
  void inOrder (Node node) {
    //cout << "inorder for " << node.key << " with left and right as " << node.left << " " << node.right << endl;

    if (node.left != -1) {
      inOrder(tree[node.left]);
    }
    nodes.push_back(node);
    if (node.right != -1) {
      inOrder(tree[node.right]);
    }
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
    t.tree.push_back(Node(key, left, right, i));
  }
  if (t.IsBinarySearchTree()) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
