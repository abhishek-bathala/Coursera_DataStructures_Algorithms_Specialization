#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

int find_overlap (string s1, string s2) {
    for (int i = 0; i < s1.size() - 12 + 1; i++) {
        if (strncmp(s2.c_str(), s1.c_str() + i, s1.size() - i) == 0) {
            return s1.size()-i;
        }
    }

    return 0;
}

int main () {
    set<string> temp_reads; //only used to ensure no duplicates, copied to vector after input
    string input;
    vector<string> reads;

    //getting input of all reads into set to remove duplicate reads
    for (int i = 0; i < 1618; i++) {
        cin >> input;
        int temp_len = temp_reads.size();
        temp_reads.insert(input);
        if (temp_len < temp_reads.size()) {
            reads.push_back(input);
            //cout << reads[reads.size()-1] << endl;
        }
    }

    string result = "";
    result += reads.front();
    string first_read = reads.front();
    string current_read = "";
    int current_index = 0;


    while (reads.size() > 1) {
        current_read = reads[current_index];
        //cout << current_read << endl;
        reads.erase(reads.begin() + current_index);

        //finding maximum overlap between non-visited reads and current read
        int max_overlap = -1;

        for (int i = 0; i < reads.size(); i++) {
            int temp_overlap = find_overlap(current_read, reads[i]);
            //cout << "tempoverlap is " << temp_overlap << endl;
            if (temp_overlap > max_overlap) {
                max_overlap = temp_overlap;
                current_index = i;
            }

        }

        result += reads[current_index].substr(max_overlap);

        //cout << "result is " << result << endl;

    }

    result.erase(0, find_overlap(reads[0], first_read));

    cout << result << endl;

}