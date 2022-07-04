#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

using std::vector;
using std::string;
using std::max;
using std::min;

int expSize;

long long eval(long long a, long long b, char op) {
  //cout << "entered eval" << endl;

  //cout << "computing " << a << op << b << endl;
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
    return 0;
  }
}

vector<long long> MinMax (int i, int j, vector<char> operators, vector<vector<long long>> minimum, vector<vector<long long>> maximum) {
  //cout << "entered minmax" << endl;
  long long min, max, a, b, c, d;
  vector<long long> returnValues(2);
  returnValues[0] = /*+2147483647*/INT8_MAX;
  returnValues[1] = /*-2147483648*/INT8_MIN;

  for (int k = i; k <= j-1; k++) {
    a = eval(maximum[i][k], maximum[k+1][j], operators[k]);
    b = eval(maximum[i][k], minimum[k+1][j], operators[k]);
    c = eval(minimum[i][k], maximum[k+1][j], operators[k]);
    d = eval(minimum[i][k], minimum[k+1][j], operators[k]);
    returnValues[0] = std::min(returnValues[0], std::min(std::min(a, b), std::min(c, d)));
    returnValues[1] = std::max(returnValues[1], std::max(std::max(a, b), std::max(c, d)));
  }

  //cout << "min is " << returnValues[0] << " & max is " << returnValues[1]<< endl;
  //cout << a << ' ' << b << ' ' << c << ' ' << d << endl;

  return returnValues;
}

long long get_maximum_value(vector<long long> numbers, vector<char> operators) {
  //cout << "entered get_max_value" << endl;
  vector<vector<long long>> minimum(numbers.size(), vector<long long>(numbers.size()));
  vector<vector<long long>> maximum(numbers.size(), vector<long long>(numbers.size()));
  vector<long long> minmaxReturn(2);
  int j = 0;

  for (int i = 0; i < numbers.size(); i++) {
    //cout << "filling base matrix" << endl;
    minimum[i][i] = (int)numbers[i];
    maximum[i][i] = (int)numbers[i];
  }

  /*cout << "printing min and max matrix" << endl;
  for (int i = 0; i < minimum.size(); i++) {
    for (int k = 0; k < minimum.size(); k++) {
      cout << minimum[i][k] << " ";
    }
    cout << endl;
  }

  cout << endl;

  for (int i = 0; i < maximum.size(); i++) {
    for (int k = 0; k < maximum.size(); k++) {
      cout << maximum[i][k] << " ";
    }
    cout << endl;
  }

  cout << endl;*/
  
  for (int s = 1; s < numbers.size(); s++) {
    for (int i = 0; i < numbers.size()-s; i++) {
      j = i + s;
      minmaxReturn = MinMax(i, j, operators, minimum, maximum);
      minimum[i][j] = minmaxReturn[0];
      maximum[i][j] = minmaxReturn[1];
      
      /*cout << "min" << endl;
      for (int i = 0; i < maximum.size(); i++) {
        for (int k = 0; k < maximum.size(); k++) {
          cout << maximum[i][k] << " ";
        }
        cout << endl;
      }
      cout << "MAX" << endl;
      for (int i = 0; i < minimum.size(); i++) {
        for (int k = 0; k < minimum.size(); k++) {
          cout << minimum[i][k] << " ";
        }
        cout << endl;
      }*/
    }
  }

  return maximum[0][numbers.size()-1];
}

int main() {
  string exp;
  vector<long long> numbers;
  vector<char> operators;
  cin >> exp;

  for (int i = 0; i < exp.size(); i++) {
    if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*') {
      operators.push_back(exp[i]);
    }
    else {
      stringstream ss;
      int temp;
      ss << exp[i];
      ss >> temp;
      numbers.push_back(temp);
    }
  }

  /*for (int i = 0; i < numbers.size(); i++) {
    cout << numbers[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < operators.size(); i++) {
    cout << operators[i] << " ";
  }*/

  cout << get_maximum_value(numbers, operators) << '\n';
}