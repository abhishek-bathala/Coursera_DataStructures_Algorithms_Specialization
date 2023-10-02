#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    //cout << "size of results vector is " << result.size() << endl;
    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<string> contacts(10000000, "not found");

    for (size_t i = 0; i < queries.size(); ++i) {
        int index = queries[i].number;
        //cout << "index is " << index << endl;
        if (queries[i].type == "add") {
            contacts[index] = queries[i].name;

            /*
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
            */

        } else if (queries[i].type == "del") {

            contacts[index] = "not found";

            /*
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
                */
        } else {
            string response = contacts[index];

            /*for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
                */
            result.push_back(response);
        }
    }
    return result;
}

int main() {

    write_responses(process_queries(read_queries()));
    return 0;
}
