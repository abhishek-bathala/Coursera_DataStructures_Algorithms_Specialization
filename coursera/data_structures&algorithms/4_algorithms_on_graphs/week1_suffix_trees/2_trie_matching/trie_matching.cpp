#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    5;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	int numOfEdges = 0;
	vector<int> startOfSuffix;

	Node ()
	{
		fill (next, next + Letters, NA);
	}
};

int letterToIndex (char letter)
{
	//cout << "checking char " << letter << endl;
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		case '$': return 4; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <bool> boolResult(text.size(), false); //true if a pattern starts at that index, false otherwise
	vector <int> result;

	//if text is only 1 character long
	if (text.size() == 1) {
		for (int i = 0; i < patterns.size(); i++) {
			if (patterns[i].size() != 1) {
				continue;
			}
			if (letterToIndex(text[0]) == letterToIndex(patterns[i][0])) {
				result.push_back(0);
			}
		}
		return result;
	}

	//constructing trie when length of text > 1
	vector <Node> trie;
	Node root;
	trie.push_back(root);
	
	for (int i = 0; i < text.size()-1; i++) {
		string suffix = text.substr(i, text.length());
		//cout << "suffix is " << suffix << endl;
		int currentNode = 0;
		for (int j = 0; j < suffix.length(); j++) {
			//cout << "\tchecking symbol " << suffix[j] << endl;
			//cout << "\tcurrentnode is " << currentNode << endl;
			if (trie[currentNode].next[letterToIndex(suffix[j])] != -1) {
				trie[currentNode].startOfSuffix.push_back(i);
				currentNode = trie[currentNode].next[letterToIndex(suffix[j])];
				//cout << "\t\tcurrentnode moving to index " << currentNode << endl;
			}
			else {
				Node newNode;
				trie.push_back(newNode);
				trie[currentNode].next[letterToIndex(suffix[j])] = trie.size()-1;
				trie[currentNode].numOfEdges++;
				trie[currentNode].startOfSuffix.push_back(i);
				currentNode = trie.size()-1;
				//cout << "\t\tadding newnode for symbol " << suffix[j] << " after " << currentNode;
				//cout << " pattern starts at " << i << endl;
			}
		}
	}

	/*int numOfBranches = 0;
	int numOfLeaves = 0;

	for (int i = 1; i < trie.size(); i++) {
		if (trie[i].numOfEdges == 0) {
			numOfLeaves++;
		}
		if (trie[i].numOfEdges > 1) {
			numOfBranches++;
		}
		
	}

	cout << "there are " << numOfLeaves << " leaves and " << numOfBranches << " branches" << endl;*/

	//finding start points of patterns in trie
	for (int i = 0; i < patterns.size(); i++) {
		string pattern = patterns[i];
		cout << "pattern is " << pattern << endl;
		int currentNode = 0;
		int indexInPattern = 0;
		while (true) {
			cout << "\tcurrentnode is " << currentNode << endl;
			if (trie[currentNode].numOfEdges == 0) {
				cout << "\t\tfound leaf at " << currentNode << endl;
				cout << "size of startings is " << trie[currentNode].startOfSuffix.size() << endl;
				for (int index = 0; index < trie[currentNode].startOfSuffix.size(); index++) {
					boolResult[trie[currentNode].startOfSuffix[index]] = true;
					cout << "index found at " << trie[currentNode].startOfSuffix[index] << endl;
				}
				break;
			}
			else if (trie[currentNode].next[letterToIndex(pattern[indexInPattern])] != -1) {
				cout << "\t\tfound branch at " << currentNode << " ";
				cout << "checking " << pattern[indexInPattern] << endl;
				currentNode = trie[currentNode].next[letterToIndex(pattern[indexInPattern])];
				indexInPattern++;
				cout << "currentnode is now " << currentNode << endl;
			}
			else {
				break;
			}
		}

	}

	//when starting index of a pattern is found, adding that index to result
	for (int i = 0; i < boolResult.size(); i++) {
		if (boolResult[i]) {
			cout << "FOUND INDEX AT " << i << endl;
			result.push_back(i);
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;
	//t = "AATCGGGTTCAATCGGGGT";
	t += "$";

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
		patterns[i] += "$";
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
