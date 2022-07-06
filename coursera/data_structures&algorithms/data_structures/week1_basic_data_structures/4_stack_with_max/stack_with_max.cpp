#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

class StackWithMax {
  public:

    vector<int> maximum;
    vector<int> stack;

    void Push(int value) {
        stack.push_back(value);
    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return maximum[maximum.size()-1];
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(stoi(value));
            if (stack.maximum.empty()) {
                stack.maximum.push_back(stoi(value));
            }
            else {
                if (stack.maximum[stack.maximum.size()-1] < stoi(value)) {
                    stack.maximum.push_back(stoi(value));
                }
                else {
                    stack.maximum.push_back(stack.maximum[stack.maximum.size()-1]);
                }
            }
        }
        else if (query == "pop") {
            //cout << "last element is " << stack.stack[stack.stack.size()-1] << endl;
            stack.maximum.pop_back();
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}