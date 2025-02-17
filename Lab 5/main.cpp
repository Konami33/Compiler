#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

using namespace std;

map<char, vector<string>> productions;

bool isNonTerminal(char symbol) {
    return productions.find(symbol) != productions.end();
}

bool parseString(const string& input, int& index, char nonTerminal) {

    // If the non-terminal is not in the productions, return false
    if (productions.find(nonTerminal) == productions.end()) {
        return false;
    }

    // Try each production rule for the current non-terminal S -> AB
    for (const string& production : productions[nonTerminal]) {
        int tempIndex = index;

        bool match = true;
        for (char symbol : production) {
            if (isNonTerminal(symbol)) {
                if (!parseString(input, tempIndex, symbol)) {
                    match = false;
                    break;
                }
            } else {
                if (tempIndex >= input.size() || input[tempIndex] != symbol) {
                    match = false;
                    break;
                }
                tempIndex++;
            }
        }

        if (match) {
            index = tempIndex;
            return true;
        }
    }

    return false;
}

int main() {
    int numProductions;
    cin >> numProductions;
    cin.ignore();

    for (int i = 0; i < numProductions; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        char nonTerminal;
        ss >> nonTerminal;

        string production;
        while (ss >> production) {
            productions[nonTerminal].push_back(production);
        }
    }

    for (const auto& rule : productions) {
        cout << "Non-terminal: " << rule.first << endl;
        for (const string& prod : rule.second) {
            cout << "  -> " << prod << endl;
        }
    }

    int test;
    cin >> test;
    while(test--) {
        string input;
        cout << "Enter the input string to parse: ";
        cin >> input;

        int index = 0;
        bool accepted = parseString(input, index, 'S');

        if (accepted && index == input.size()) {
            cout << "Input string \"" << input << "\" is ACCEPTED by the CFG." << endl;
        } else {
            cout << "Input string \"" << input << "\" is REJECTED by the CFG." << endl;
        }
    }

    return 0;
}