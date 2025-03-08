#include<bits/stdc++.h>
using namespace std;
void printStack(stack<char> s) {
    stack<char> tmp = s;
    while (!tmp.empty()) {
        cout << tmp.top();
        tmp.pop();
    }
}
int main() {
    map<char, map<char, string>> productions; // Map to store productions
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        char nonTerminal, terminal;
        string production;
        cin >> nonTerminal >> terminal >> production;
        productions[nonTerminal][terminal] = production;
    }

    string input;
    cin >> input;
    stack<char> parseStack, inputStack;

    for (int i = input.size() - 1; i >= 0; i--) {
        inputStack.push(input[i]);
    }

    parseStack.push('$'); // End marker
    parseStack.push('E'); // Start symbol
    string matched = "";
    cout << "Stack\t\tInput\t\tMatched" << endl;

    while (true) {

        printStack(parseStack);
        cout << "\t\t";
        printStack(inputStack);
        cout << "\t\t";
        cout << matched << endl;

        if (parseStack.size() == 1 && inputStack.size() == 1) {
            cout << "Accepted" << endl;
            break;
        }

        char stackTop = parseStack.top();
        char inputTop = inputStack.top();

        // pop the top elements to match
        if (stackTop == inputTop) {
            matched.push_back(stackTop);
            parseStack.pop();
            inputStack.pop();
            continue;
        }

        if (productions[stackTop][inputTop].empty()) { // No rule
            cout << "Rejected" << " " << stackTop << inputTop << endl;
            return 0;
        }

        parseStack.pop();
        string production = productions[stackTop][inputTop];

        // epsilon production
        if (production != "0") {
            for (int i = production.size() - 1; i >= 0; i--) {
                parseStack.push(production[i]);
            }
        }
    }
    return 0;
}