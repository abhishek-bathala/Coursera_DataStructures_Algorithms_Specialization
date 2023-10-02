#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

void find_multiple_outgoing(unordered_map<string, vector<string> > &db_g, vector<string> &nodes_out) {
    //cout << "outgoing" << endl;
    for (auto itr = db_g.begin(); itr != db_g.end(); itr++) {
        if (itr->second.size() > 1) {
            //cout << itr->first << endl;
            nodes_out.push_back(itr->first);
        }
    }

}

void find_multiple_incoming(unordered_map<string, vector<string> > &incoming, vector<string> &nodes_in) {
    //cout << "incoming" << endl;
    for (auto itr = incoming.begin(); itr != incoming.end(); itr++) {
        if (itr->second.size() > 1) {
            //cout << itr->first << endl;
            nodes_in.push_back(itr->first);
        }
    }
}

void alternate_input (int k, int t, string &read, set<string> &ReadsSet) {
    int len = 100; 

    cin >> k >> t; 

    while( std::cin >> read ){
        if( (int)read.size() != len ){ 
            break;
        }
        
        else {
            if( ReadsSet.count( read ) == 0 ){
                ReadsSet.insert( read ); 
            }
        }
    }
}

void dfs (string &cur, vector<vector<string>> &paths, vector<string> &path, unordered_map<string, vector<string>> &db_g, int t, unordered_map<string, bool> &visited, vector<string> &nodes_in) {
    if (path.size() >= t) {
        return;
    }

    //cout << "visited " << cur << endl;

    visited[cur] = true;
    path.push_back(cur);
    bool cur_in_nodesin = false;
    for (auto x : nodes_in) {
        if (cur == x) {
            cur_in_nodesin = true;
            break;
        }
    }

    //cout << cur << " has >1 incoming " << cur_in_nodesin << endl;

    /*if (path.size() > 0 && cur_in_nodesin) {
        paths.push_back(path);
        //cout << "found 1 path" << endl;
        for (auto x : path) {
            cout << x << " ";
        }
        cout << endl;
    }
    */

    for (auto x : db_g[cur]) {
        if (!visited[x]) {
            dfs(x, paths, path, db_g, t, visited, nodes_in);
        }
    }

    visited[cur] = false;
    path.pop_back();

}

bool is_disjoint_path (vector<string> &path1, vector<string> &path2) {

    if (path1[0] != path2[0] || path1[path1.size()-1] != path2[path2.size()-1]) {
        return false;
    }
    for (int x = 1; x < path1.size()-1; x++) {
        for (int y = 1; y < path2.size()-1; y++) {
            if (path1[x] == path2[y]) {
                return false;
            }
        }
    }

    return true;
}

int find_count_bubbles (unordered_map <string, vector<string> > &db_g, unordered_map <string, vector<string> > &incoming, vector<string> &nodes_out, vector<string> &nodes_in, int t) {
    int num_of_bubbles = 0;
    vector<vector<string> > paths; //all possible paths between two nodes


    for (int i = 0; i < nodes_out.size(); i++) {
        unordered_map <string, bool> visited;
        vector<string> path;
        for (auto itr = db_g.begin(); itr != db_g.end(); itr++) {
            visited[itr->first] = false;
        }

        dfs(nodes_out[i], paths, path, db_g, t, visited, nodes_in);

        //cout << paths.size() << " paths found" << endl;

        if (!paths.empty()) {
            for (int i = 0; i < paths.size() - 1; i++) {
                for (int j = i + 1; j < paths.size(); j++) {
                    if (is_disjoint_path(paths[i], paths[j])) {
                        num_of_bubbles++;
                    }
                }
            }
        }
    }

    return num_of_bubbles;

}

int main() {
    set<string> temp_kmers; //only used to ensure no duplicates, copied to vector after input
    vector<string> kmers; //list of kmers, string indices in this correspond to information in incoming, nodes_out, nodes_in, and de_bruijn_g
    vector<pair<string, string> > lr_k_mers; //pair of left and right k-1 mers
    //string input;
    unordered_map <string, vector<string> > de_bruijn_g;
    unordered_map <string, vector<string> > incoming;
    vector<string> nodes_out;
    vector<string> nodes_in;
    int k, t;

    cin >> k >> t;

    //getting input of all reads, generating kmers into set to remove duplicates
    for (string input; cin >> input;) {
    //while (cin >> input) {
        /*if ((int)input.size() != 100;) {
            cout << "12345";
            return 0;
        }*/
        
        for (int i = 0; i+k <= input.length(); i++) {
            string temp_kmer = input.substr(i, k);
            //cout << "substr is " << temp_kmer << endl;
            int temp_len = temp_kmers.size();
            temp_kmers.insert(temp_kmer);
            if (temp_len < temp_kmers.size()) {
                kmers.push_back(temp_kmer);
                lr_k_mers.push_back(make_pair(temp_kmer.substr(0, temp_kmer.length()-1), temp_kmer.substr(1, temp_kmer.length()-1)));
                de_bruijn_g[lr_k_mers[lr_k_mers.size()-1].first].push_back(lr_k_mers[lr_k_mers.size()-1].second);
                //cout << "kmer: " << kmers[kmers.size()-1] << endl;
                //cout << "left: " << lr_k_mers[lr_k_mers.size()-1].first << " right: " << lr_k_mers[lr_k_mers.size()-1].second << endl;
                incoming[lr_k_mers[lr_k_mers.size()-1].second].push_back(lr_k_mers[lr_k_mers.size()-1].first);
            }
        }
    }

    //cout << "printing db graph" << endl;
    /*for (auto itr = de_bruijn_g.begin(); itr != de_bruijn_g.end(); itr++) {
        cout << itr->first << ": ";
        for (int i = 0; i < itr->second.size(); i++) {
            cout << itr->second[i] << " ";
        }
        cout << endl;
    }
    */
    
   find_multiple_incoming(incoming, nodes_in);
   find_multiple_outgoing(de_bruijn_g, nodes_out);

   cout << find_count_bubbles(de_bruijn_g, incoming, nodes_out, nodes_in, t) << endl;


    
}