#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  int temp = 0;

  for (int i = 0; i < values.size(); i++) {
    for (int j = i; j < values.size(); j++) {
      if((double)values.at(i)/(double)weights.at(i) < (double)values.at(j)/(double)weights.at(j)) {
        temp = values.at(i);
        values.at(i) = values.at(j);
        values.at(j) = temp;

        temp = weights.at(i);
        weights.at(i) = weights.at(j);
        weights.at(j) = temp;

      }
    }
  }

  /*cout << "Printing sorted items" << endl;
  for (auto x : values) {
    cout << x << endl;
   }

  for (auto x : weights) {
    cout << x << endl;
  }*/

  for (int i = 0; i < values.size(); i++) {
    if (capacity == 0) {
      return value;
    }

    if (capacity >= weights.at(i)) {
      value += values.at(i);
      capacity -= weights.at(i);
    }
    else if (capacity < weights.at(i)) {
      value += values.at(i)*((double)capacity/(double)weights.at(i));
      return value;
    }
  }
  
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  cout.precision(10);
  cout << optimal_value << endl;
  return 0;
}
