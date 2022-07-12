#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
		if (table != sets[table].parent) {
			sets[table].parent = getParent(sets[table].parent);
		}
		return sets[table].parent;
		
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		int finalSize = -1;
		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
			if (sets[realDestination].rank > sets[realSource].rank) {
				sets[realSource].parent = realDestination;
				//max_table_size += sets[realDestination].size;
				//cout << endl << "first if" << endl;
				//cout << "merged " << realDestination+1 << " to bottom of " << realSource+1 << endl;
				//cout << "size of " << realDestination+1 << " is " << sets[realDestination].size << ", " << realSource+1 << " is " << sets[realSource].size << endl;
				sets[realDestination].size += sets[realSource].size;
				//cout << "FINAL SIZE IS " << sets[realDestination].size << endl;
				finalSize = sets[realDestination].size;

			}
			else {
				//cout << endl << "else" << endl;
				sets[realDestination].parent = realSource;
				//cout << "merged " << realSource+1 << " to bottom of " << realDestination+1 << endl;
				//cout << "size of " << realSource+1 << " is " << sets[realSource].size << ", " << realDestination+1 << " is " << sets[realDestination].size << endl;
				/*if (sets[realDestination].size == sets[realSource].size) {
					sets[realSource].rank++;
				}*/
				sets[realSource].size += sets[realDestination].size;
				//cout << "FINAL SIZE IS " << sets[realSource].size << endl;
				finalSize = sets[realSource].size;
			}

			if (finalSize > max_table_size) {
				max_table_size = finalSize;
			}
                        // update max_table_size
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
