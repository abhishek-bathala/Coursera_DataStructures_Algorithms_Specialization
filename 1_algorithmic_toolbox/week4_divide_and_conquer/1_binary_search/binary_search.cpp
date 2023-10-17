#include <iostream>
#include <cassert>
#include <vector>

using std::vector;
using namespace std;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size();
  int mid = (left+right)/2;
  //cout << "\n" << "finding " << x << endl;

  while (left <= right && mid < a.size() && mid >= 0) {
    //cout << "left is " << left << " right is " << right << " mid is " << mid << endl;
    //cout << "comparing " << a.at(mid) << " with " << x << endl;
    if (a.at(mid) == x) {
      return mid;
    }
    else if (a.at(mid) < x) {
      left = mid + 1;
    }
    else if (a.at(mid) > x) {
      right = mid - 1;
    }
    
    mid = (left+right)/2;
  }

  return -1;

}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
