#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	int indexInText;

	Node ()
	{
		fill (next, next + Letters, NA);
		indexInText = -1;
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

void search (string& pattern, string& text, vector <bool>& isStart) {
	//cout << "searching for " << pattern << endl;

	vector<int> shift(pattern.size(), -1);

	for (int i = 0; i < shift.size(); i++) {
		shift[letterToIndex(pattern[i])] = i;
		//cout << shift[letterToIndex(pattern[i])];
	}
	//cout << endl;

	int shiftNum = 0;

	while (shiftNum <= text.size()-pattern.size()) {
		int patternIndex = pattern.size() - 1;
		//cout << "patternindex is " << patternIndex << endl;

		while (patternIndex >= 0 && pattern[patternIndex] == text[shiftNum + patternIndex]) {
			patternIndex--;
		}
		//cout << "now patternindex is " << patternIndex << endl;

		if (patternIndex < 0) {
			//cout << "\tpattern found at " << shiftNum << endl;
			isStart[shiftNum] = true;

			if (shiftNum + pattern.size() < text.size()) {
				shiftNum += pattern.size() - shift[letterToIndex(text[shiftNum+pattern.size()])];
			}
			else {
				shiftNum += 1;
			}
		}

		else {
			shiftNum += max(1, patternIndex - shift[letterToIndex(text[shiftNum + patternIndex])]);
		}
	}

}


vector <int> solve (string& text, int n, vector <string>& patterns)
{
	vector <int> result;
	/*vector <Node> trie;
	Node root;
	int currentnode = 0;
	trie.push_back(root);

	for (int i = 0; i < text.size(); i++) {
		currentnode = 0;
		string suffix = text.substr(i, text.length());
		//cout << "substring is " << suffix << endl;
		for (int j = 0; j < suffix.length(); j++) {
			cout << "currentnode is " << currentnode << endl;
			if (trie[currentnode].next[letterToIndex(suffix[j])] != NA) {
				currentnode = trie[currentnode].next[letterToIndex(suffix[j])];
				cout << "\tcurrentnode moved to " << currentnode << endl;
			}
			else {
				Node newNode;
				newNode.indexInText = i+j;
				trie.push_back(newNode);
				trie[currentnode].next[letterToIndex(suffix[j])] = trie.size()-1;
				cout << "\tadded " << suffix[j] << " to trie at index " << trie[currentnode].next[letterToIndex(suffix[j])];
				cout << " with index in text of " << newNode.indexInText << endl;
				currentnode = trie[currentnode].next[letterToIndex(suffix[j])];
				cout << "\t\tcurrentnode moved to " << currentnode << endl;
			}
		}

	}*/

	vector<bool> isStart(text.size());

	for (int i = 0; i < patterns.size(); i++) {
		if (patterns[i].size() > text.size()) {
			continue;
		}
		search(patterns[i], text, isStart);
	}

	for (int i = 0; i < isStart.size(); i++) {
		if (isStart[i]) {
			result.push_back(i);
		}
	}

	//cout << result.size() << endl;

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
