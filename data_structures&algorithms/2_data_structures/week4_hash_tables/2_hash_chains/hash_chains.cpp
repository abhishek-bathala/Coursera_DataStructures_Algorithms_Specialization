#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    size_t hash_func(const string& s) const {
        //cout << "hash function" << endl;
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQueries() {
        //cout << "processing" << endl;
        vector<vector<string>> elems(bucket_count);
        //cout << "size of elems is " << elems.size() << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            Query query = readQuery();
            if (query.type == "check") {
            // use reverse order, because we append strings to the end
                for (int i = elems[query.ind].size()-1; i >= 0; i--) {
                    cout << elems[query.ind].at(i) << " ";
                }
                cout << endl;
            } else {
                size_t hashValue = hash_func(query.s);
                if (query.type == "find") {
                    //cout << "finding" << endl;
                    bool found = false;

                    for (int i = 0; i < elems[hashValue].size(); i++) {
                        if (elems[hashValue].at(i) == query.s) {
                            found = true;
                            break;
                        }
                    }
                    writeSearchResult(found);
                }
                else if (query.type == "add") {
                    //cout << "adding" << endl;
                    bool found = false;
                    for (int i = 0; i < elems[hashValue].size(); i++) {
                        if (elems[hashValue].at(i) == query.s) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        elems[hashValue].push_back(query.s);
                        //cout << "added " << query.s << " to " << hashValue << " size is now " << elems[hashValue].size() << endl;
                    }

                } else if (query.type == "del") {
                    //cout << "deleting hash " << hashValue << " with size " << elems[hashValue].size() << endl;
                    for (int i = 0; i < elems[hashValue].size(); i++) {
                        //cout << "comparing " << query.s << " with " << elems[hashValue].at(i);
                        if (elems[hashValue].at(i) == query.s) {
                            //cout << "deleted" << query.s << " from " << hashValue << endl;
                            elems[hashValue].erase(elems[hashValue].begin() + i);
                            break;
                        }
                    }

                }
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
