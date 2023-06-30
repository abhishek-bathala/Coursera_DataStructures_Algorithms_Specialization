#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct mer {
    string left_mer;
    string right_mer;
    string mer;
    int id;
    vector<int> outgoing;
    int incoming;
    bool in_graph;
};

int main() {
    set<string> reads;

    for (int i = 0; i < 10; i++) {
        string temp;
        cin >> temp;
        reads.insert(temp);
    }

    //generating 15-mers (of length 14)
    set<string> temp_mers;
    vector<mer> fifteen_mers;
    int temp_id = 0;

    for (auto read : reads) {
        for (int i = 0; i < read.length() - 2; i++) {
            string str = read.substr(i, 3);
            int temp_length = temp_mers.size();
            temp_mers.insert(str);

            if (temp_length < temp_mers.size()) {
                mer temp;
                temp.id = temp_id;
                temp.mer = str;
                temp.left_mer = str.substr(0, str.size()-1);
                temp.right_mer = str.substr(1, str.size()-1);
                temp.in_graph = false;
                cout << temp.id << " " << temp.mer << " " << temp.left_mer << " " << temp.right_mer << endl;
                fifteen_mers.push_back(temp);
                temp_id++;

            }
        }
    }

    //build de bruijn graph from mers
    int used = 0;
    int current = 0;

    while (used != fifteen_mers.size()) {
        for (auto x : fifteen_mers) {
            if (x.id != current && fifteen_mers[current].right_mer == x.left_mer && !x.in_graph) {
                fifteen_mers[current].outgoing.push_back(x.id);
                x.incoming++;
                used++;
                x.in_graph = true;
                cout << "edge between " << current << " and " << x.id << endl;
                current = x.id;
                break;
            }
        }
    }


}