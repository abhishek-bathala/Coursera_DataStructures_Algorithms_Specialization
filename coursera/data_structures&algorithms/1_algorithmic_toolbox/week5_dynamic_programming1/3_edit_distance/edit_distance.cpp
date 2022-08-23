#include <iostream>
#include <string>
#include <vector>

using namespace std;

int min (int a, int b, int c) {
  int min = 0;

  while (a > 0 && b > 0 && c > 0) {
    a--;
    b--;
    c--;
    min++;
  }

  return min;
}

int edit_distance(const string &str1, const string &str2) {
  if (str1 == str2) {
    return 0;
  }

  int editDistance[str1.size()+1][str2.size()+1];
  editDistance[0][0] = 0;
  for (int i = 0; i <= str1.size(); i++) {
    editDistance[i][0] = i;
  }
  for (int j = 0; j <= str2.size(); j++) {
    editDistance[0][j] = j;
  }

  for (int i = 1; i <= str1.size(); i++) {
    for (int j = 1; j <= str2.size(); j++) {
      int insert = editDistance[i][j-1] + 1;
      int deletion = editDistance[i-1][j] + 1;
      int match = editDistance[i-1][j-1];
      int mismatch = editDistance[i-1][j-1] + 1;

      if (str1[i-1] == str2[j-1]) {
        editDistance[i][j] = min(insert, deletion, match);
        //cout << editDistance[i][j];
      }
      else {
        editDistance[i][j] = min(insert, deletion, mismatch);
        //cout << editDistance[i][j];
      }
      //cout << " ";
    }
    //cout << endl;
  }


  /*for (int i = 0; i <= str1.size(); i++) {
    for (int j = 0; j <= str2.size(); j++) {
      cout << editDistance[i][j] << " ";
    }
    cout << endl;
  }*/

  return editDistance[str1.size()][str2.size()];
}


int main() {
  string str1;
  string str2;
  cin >> str1 >> str2;
  cout << edit_distance(str1, str2) << std::endl;
  return 0;

}
