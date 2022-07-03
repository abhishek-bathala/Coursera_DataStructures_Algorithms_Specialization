#include <iostream>
#include <vector>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
  vector<vector<int>> optimalWeight(w.size()+1, vector<int>(W+1));
  int value = 0;

  for (int i = 0; i <= w.size(); i++) {
    optimalWeight[i][0] = 0;
  }
  for (int j = 0; j <= W; j++){
    optimalWeight[0][j] = 0;
  }

  for (int i = 1; i <= w.size(); i++) {
    for (int j = 1; j <= W; j++) {
      optimalWeight[i][j] = optimalWeight[i-1][j];

      if (w[i-1] <= j) {
        value = optimalWeight[i-1][j-w.at(i-1)] + w[i-1];
        //cout << "value of " << i << " " << j << " is " << value << " and already is " << optimalWeight[i][j] << endl;

        if (value > optimalWeight[i][j]) {
          optimalWeight[i][j] = value;
        }
      }
    }
  }

  /*cout << endl;
  for (int i = 0; i <= w.size(); i++) {
    for (int j = 0; j <= W; j++) {
      cout << optimalWeight[i][j] << " ";
    }
    cout << endl;
  }*/

  return optimalWeight[w.size()][W];
}

int main() {
  int n, W;
  cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  cout << optimal_weight(W, w) << '\n';
}
