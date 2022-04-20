#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  //if (left == right) return -1;
  //if (left + 1 == right) return a[left];

  int temp = 0;
  int count_maj_num = 1;
  int maj_num = a.at(0);

  for (int i = 1; i < a.size(); i++) {
    if (count_maj_num == 0) {
      maj_num = a.at(i);
      count_maj_num = 1;
    }
    else {
      if (maj_num == a.at(i)) {
        count_maj_num++;
      }
      else {
        count_maj_num--;
      }
    }
  //cout << "num is " << maj_num << " and count is " << count_maj_num << endl;
  }

  for (int i = 0; i < a.size(); i++) {
    if (a.at(i) == maj_num) {
      temp++;
    }
  }

  if (temp > a.size()/2) {
    return 1;
  }
  return 0;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  cout << get_majority_element(a, 0, a.size()-1) << '\n';
}
