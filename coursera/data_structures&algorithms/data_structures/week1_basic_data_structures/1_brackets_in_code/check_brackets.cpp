#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    string text;
    getline(cin, text);

    stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            Bracket temp(next, position+1);
            opening_brackets_stack.push(temp);
        }

        if (next == ')' || next == ']' || next == '}') {
            if (!opening_brackets_stack.empty()) {
                if (opening_brackets_stack.top().Matchc(next)) {
                    opening_brackets_stack.pop();
                }
                else {
                   cout << position+1 << endl;
                   return 0;
                }
            }
            else {
                cout << position+1 << endl;
                return 0;
            }
        }
    }

    if (opening_brackets_stack.empty()) {
        cout << "Success" << endl;
    }
    else {
        while (opening_brackets_stack.size() != 1) {
            opening_brackets_stack.pop();
        }
        cout << opening_brackets_stack.top().position << endl;
    }

    return 0;
}
