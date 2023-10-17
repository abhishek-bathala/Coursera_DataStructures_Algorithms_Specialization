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
// vector with all positions in the text (starting from 1) where 
// the pattern starts in the text.
void find_pattern(const string& pattern, const string& text, vector<bool> &results) {
  // Implement this function yourself
  string s = pattern + "$" + text;

  vector<int> prefixes(s.length());
  //cout << "prefix length is " << prefixes.size() << endl;
  computePrefixes(prefixes, s);

  for (int i = pattern.length()+1; i < s.length(); i++) {
    if (prefixes[i] == pattern.length()) {
      results[i-2*pattern.length()] = true;
    }
  }
}

int main() {
  string text;
  cin >> text;

  int n;
  cin >> n;
  
  vector<string> patterns (n);
  vector<bool> results (text.length());
  for (int i = 0; i < n; i++) {
    cin >> patterns[i];
    find_pattern(patterns[i], text, results);
  }

  for (int i = 0; i < results.size(); ++i) {
    if (results[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
