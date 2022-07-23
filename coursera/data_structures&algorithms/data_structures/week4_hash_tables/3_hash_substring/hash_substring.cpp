#include <iostream>
#include <string>
#include <vector>

typedef unsigned long long ull;

using namespace std;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

long long polyHash(string string, long long p, long long x) {
    long long hash = 0;

    for (int i = string.length()-1; i >= 0; i--) {
        hash = (hash*x + (int)string[i]) % p;
    }

    cout << "polyhash is " << hash << endl;
    return hash;
}

vector<long long> precomputeHashes(string text, int patternLength, long long p, long long x) {
    cout << "precomputing" << endl;
    vector<long long> hashes(text.length()-patternLength+1);
    string substring = text.substr(text.length()-patternLength, text.length()-1);
    hashes[text.length()-patternLength] = polyHash(text, p, x);
    int y = 1;

    for (int i = 1; i < patternLength; i++) {
        y = (y*x) % p;
    }

    for (int i = text.length()-patternLength-1; i >= 0; i--) {
        hashes[i] = (x*hashes[i+1] + (int)text[i] - y*text[i + patternLength]) % p;
    }

    return hashes;
}

bool areEqual (string s1, string s2) {
    cout << "areequal" << endl;
    if (s1.length() != s2.length()) {
        return false;
    }

    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }

    return true;
}

vector<int> rabinKarp(string text, string pattern)  {
    long long p = 99999999977;
    long long x = 1;
    vector<int> positions;
    long long pHash = polyHash(pattern, p, x);
    vector<long long> hashes = precomputeHashes(text, pattern.length(), p, x);

    for (int i = 0; i < text.length()-pattern.length(); i++) {
        cout << "i is " << i << endl;
        if (pHash != hashes[i]) {
            continue;
        }
        if (areEqual(text.substr(i+pattern.length()-1), pattern)) {
            cout << "pushingback" << endl;
            positions.push_back(i);
        }
    }

    return positions;

}

void print_occurrences(const vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        cout << output[i] << " ";
    cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
    /*const string& s = input.pattern, t = input.text;
    vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;*/

    return rabinKarp(input.text, input.pattern);
}


int main() {
    ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
