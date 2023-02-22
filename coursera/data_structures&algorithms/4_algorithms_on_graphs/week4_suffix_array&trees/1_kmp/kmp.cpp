#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void computePrefixes(vector<int> &prefixes, string& s){
  int border = 0;
  prefixes[0] = 0;
  for (int i = 1; i < s.length(); i++) {

    while (border > 0 && s[i] != s[border]) {
      border = prefixes[border-1];
    }

    if (s[i] == s[border]) {
      border++;
    }
    else {
      border = 0;
    }
    prefixes[i] = border;
  }
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string s = pattern + "$" + text;

  vector<int> prefixes(s.length());
  //cout << "prefix length is " << prefixes.size() << endl;
  computePrefixes(prefixes, s);

  for (int i = pattern.length()+1; i < s.length(); i++) {
    if (prefixes[i] == pattern.length()) {
      result.push_back(i-2*pattern.length());
    }
  }

  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
