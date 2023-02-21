#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Transform
{
  string rotatedText;
  int index;

  Transform(string t, int i) {
    rotatedText= t;
    index = i;
  }

  bool operator< (const Transform &x) {
    return rotatedText < x.rotatedText;
  }
};


string BWT(const string& text) {
  string result = "\n";

  vector <Transform> rotations;

  for (int i = 0; i < text.length(); i++) {
    string rotation;
    if (i != 0) {
       rotation = text.substr(i) + text.substr(0, i);
    }
    else {
      rotation = text;
    }
    rotations.push_back(Transform(rotation, i));

   //cout << rotations[i].rotatedText << endl;
  }

  sort(rotations.begin(), rotations.end());
  //cout << "\tAFTER SORTING" << endl;
  for (int i = 0; i < rotations.size(); i++) {
    //cout << i << ": " << rotations[i].rotatedText << endl;
    result += rotations[i].rotatedText.at(text.length()-1);
  }    

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}