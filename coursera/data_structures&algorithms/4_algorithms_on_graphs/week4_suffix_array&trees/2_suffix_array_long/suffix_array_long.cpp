#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;


vector<int> sortCharacters (string& text) {
  //cout << "sortcharacters" << endl;
  vector<int> order(text.length());
  vector<int> count(85, 0);
  char c;

  for (int i = 0; i < text.length(); i++) {
    count[text[i]] = count[text[i]] + 1;
  }
  for (int j = 1; j <= 84; j++) {
    count[j] = count[j] + count[j-1];
  }
  for (int i = text.length()-1; i >= 0; i--) {
    c = text[i];
    count[c] = count[c] - 1;
    order[count[c]] = i;
  }

  /*for (int i = 0; i < order.size(); i++) {
    cout << order[i] << " ";
  }
  cout << endl;*/


  return order;
}

vector<int> computeCharClasses (string& text, vector<int>& order) {
  //cout << "computecharclasses" << endl;
  vector<int> classes(text.length());
  classes[order[0]] = 0;
  for (int i = 1; i < text.length(); i++) {
    if (text[order[i]] != text[order[i-1]]) {
      classes[order[i]] = classes[order[i-1]] + 1;
    }
    else {
      classes[order[i]] = classes[order[i-1]];
    }
  }
  return classes;
}

vector<int> sortDoubled (string& text, int& length, vector<int>& order, vector<int>& classes) {
  //cout << "sortdoubled" << endl;
  vector<int> count(text.length());
  vector<int> newOrder(text.length(), 0);
  int start, cl;

  for (int i = 0; i < text.length(); i++) {
    count[classes[i]] = count[classes[i]] + 1;
  }
  for (int j = 1; j < text.length(); j++) {
    count[j] = count[j] + count[j-1];
  }
  for (int i = text.length()-1; i >= 0; i--) {
    start = (order[i] - length + text.length()) % text.length();
    cl = classes[start];
    count[cl] = count[cl] - 1;
    newOrder[count[cl]] = start;
  }
  return newOrder;
}

vector<int> updateClasses (vector<int>& newOrder, vector<int>& classes, int& length) {
  vector<int> newClass(newOrder.size());
  newClass[newOrder[0]] = 0;
  int cur, prev, mid, midPrev;

  for (int i = 1; i < newOrder.size(); i++) {
    cur = newOrder[i];
    prev = newOrder[i-1];
    mid = cur + length;
    midPrev = (prev + length) % newOrder.size();
    if ((classes[cur] != classes[prev]) || (classes[mid] != classes[midPrev])) {
      newClass[cur] = newClass[prev] + 1;
    }
    else {
      newClass[cur] = newClass[prev];
    }
  }
  return newClass;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(string& text) {
  // Implement this function yourself
  vector<int> order(text.length());
  vector<int> classes(text.length());
  int length = 1;

  order = sortCharacters(text);
  classes = computeCharClasses(text, order);

  while (length < text.length()) {
    order = sortDoubled(text, length, order, classes);
    classes = updateClasses(order, classes, length);
    length *= 2;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
