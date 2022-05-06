#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> greedy_optimal_sequence(int n) {
  vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> dp_optimal_sequence(int n) {
  vector<int> sequence;
  sequence.push_back(0); //accounting for 0
  sequence.push_back(0); //accounting for 1
  vector<int> operations;
  operations.push_back(2);
  operations.push_back(3);

  for (int i = 2; i <= n; i++) {
    sequence.push_back(sequence.at(i-1)+1);
    //cout << "i is at " << i << endl;

    for (int j = 0; j < 2; j++) {
      if (i % operations[j] == 0) {
        //cout << " " << i << " is divisible by " << operations[j] << endl;
        int numOfOperations = sequence.at((i/operations[j])) + 1;
        //cout << "  num of operations is " << numOfOperations << endl;
        if (sequence.at(i) > numOfOperations) {
          sequence[i] = numOfOperations;
        }
      }
    }
   
    //cout << "for " << i << " min operations is " << sequence.at(i) << endl;
  }

  /*cout << sequence.at(sequence.size()-1) << endl;

  cout << "index: ";
  for (int i = 0; i < sequence.size(); i++) {
    cout << i << " ";
  }
  cout << endl;

  cout << "opNum: ";
  for (int i = 0; i < sequence.size(); i++) {
    cout << sequence.at(i) << " ";
  }
  cout << endl;
*/


  vector<int> order;
  order.push_back(n);
  int index = n;
  /*for (int i = 0; i <= sequence.at(sequence.size()-1); i++) {*/
  while (sequence.at(index) != 1 && sequence.at(index) != 0) {
    //cout << "index at " << index << endl;

    if(index % 3 == 0 && index > 3 && (sequence.at(index)-1 == sequence.at(index/3))) {
      //cout << index << " divisible by 3" << endl;
      index /= 3;
    }
    else if (index % 2 == 0 && index > 2  && (sequence.at(index) == sequence.at(index/2)+1)) {
      //cout << index << " divisible by 2" << endl;
      //cout << "    half is " << index/2 << " containing " << sequence.at(index/2) << endl;
      index /= 2;
    }
    else {
      //cout << "plus 1" << endl;
      index--;
    }

    order.push_back(index);

  }

  if (order.at(order.size()-1) != 1) {
    order.push_back(1);
  }

  reverse(order.begin(), order.end());

  return order;
}

int main() {
  int n;
  cin >> n;
  vector<int> sequence = dp_optimal_sequence(n);
  cout << sequence.size() - 1 << endl;
  for (size_t i = 0; i < sequence.size(); i++) {
    cout << sequence[i] << " ";
  }
}