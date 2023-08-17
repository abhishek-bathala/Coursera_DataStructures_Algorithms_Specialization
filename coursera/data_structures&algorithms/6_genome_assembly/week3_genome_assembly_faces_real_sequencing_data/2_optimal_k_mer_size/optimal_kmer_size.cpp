#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
#include <set>

using namespace std;

int find_overlap(vector<string> &reads) {
    int result = INT_MAX;

    for (int i = 0; i < reads.size(); i++) {
        for (int j = 0; j < reads.size(); j++) {
            if (i != j) {
                for (int k = 0; k < 100; k++) {
                    int mer = k;

                    for (int l = 0; mer < 100; mer++, l++) {
                        if (reads[i][mer] != reads[j][l]) {
                            break;
                        }
                    }

                    if (mer == 100) {
                        result = min(result, 100 - k);
                    }
                }
            }
        }
    }

    return result;
}


int main() {
    vector<string> reads;
    string input;
    set<string> temp_reads;

    for (int i = 0; i < 400; i++) {
        cin >> input;
        int temp_len = temp_reads.size();
        temp_reads.insert(input);

        if (temp_reads.size() > temp_len) {
            reads.push_back(input);
        }
    }

    cout << find_overlap(reads) << endl;
}