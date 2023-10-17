#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

using std::vector;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size();
  int mid = (left/+right)/2;

  while (left <= right && mid < a.size() && mid >= 0) {
    //cout << "left is " << left << " right is " << right << " mid is " << mid << endl;
    //cout << "comparing " << a.at(mid) << " with " << x << endl;
    if (a.at(mid) == x) {
      for (int i = mid; i > 0 && a.at(i) == x; i--, mid--){
        //cout << "comparing " << a.at(mid) << " with " << a.at(mid-1) << endl;
        if (a.at(mid-1) == x) {
          continue;
        }
        else {
          break;
        }
      }

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
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  int m;
  cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    cout << binary_search(a, b[i]) << ' ';
  }
}
