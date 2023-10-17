#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct FirstColumn
{
  char letter;
  int index;

  FirstColumn(char c, int i) {
    letter = c;
    index = i;
  }

  bool operator< (const FirstColumn &x) {
    if (letter == x.letter) {
      return index < x.index;
    }
    return letter < x.letter;
  }
};

string InverseBWT(const string& bwt) {
  string text = "";
  string lastColumn = bwt;

  vector<FirstColumn> firstColumn;
  for (int i = 0; i < bwt.length(); i++) {
    firstColumn.push_back(FirstColumn(bwt[i], i));
  }

  sort(firstColumn.begin(), firstColumn.end());

  int index = 0;
  for (int i = 0; i < firstColumn.size(); i++) {
    //cout << firstColumn[i].letter << firstColumn[i].index << endl;
    index = firstColumn[index].index;
    text += firstColumn[index].letter;
    //cout << text << endl;
  }
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
