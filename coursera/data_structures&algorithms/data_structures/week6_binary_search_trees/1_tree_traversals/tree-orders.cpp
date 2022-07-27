#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  vector <int> result;

  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }

    /*cout << "key contains ";
    for (int i = 0; i < n; i++) {
      cout << key[i] << " ";
    }
    cout << endl << "left contains ";
    for (int i = 0; i < n; i++) {
      cout << left[i] << " ";
    }
    cout << endl << "right contains ";
    for (int i = 0; i < n; i++) {
      cout << right[i] << " ";
    }*/

  }


  void in_order() {
    //cout << endl << "entered inorder" << endl;
    result.clear();
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (key[0] == -1) {
      return;
    }
    in_order_helper(left[0]);
    result.push_back(key[0]);
    in_order_helper(right[0]);

  }

  void pre_order() {
    result.clear();
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (key[0] == -1) {
      return;
    }
    result.push_back(key[0]);
    pre_order_helper(left[0]);
    pre_order_helper(right[0]);
  }

  void post_order() {
    result.clear();
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (key[0] == -1) {
      return;
    }
    post_order_helper(left[0]);
    post_order_helper(right[0]);
    result.push_back(key[0]);
  }

  void print() {
    //cout << "entered print" << endl;
    for (size_t i = 0; i < result.size(); i++) {
      if (i > 0) {
        cout << ' ';
      }
      cout << result[i];
    }
    cout << '\n';
  }

private:
  void in_order_helper(int i) {
    //cout << "int i is " << i << endl;
    if (i == -1) {
      return;
    }
    //print();

    in_order_helper(left[i]);
    result.push_back(key[i]);
    in_order_helper(right[i]);

  }

  void pre_order_helper(int i) {
    if (i == -1) {
      return;
    }
    //print();

    result.push_back(key[i]);
    pre_order_helper(left[i]);
    pre_order_helper(right[i]);

  }

  void post_order_helper(int i) {
    if (i == -1) {
        return;
      }
    //print();

    post_order_helper(left[i]);
    post_order_helper(right[i]);
    result.push_back(key[i]);
  }

};

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  t.in_order();
  t.print();
  t.pre_order();
  t.print();
  t.post_order();
  t.print();
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
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
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

