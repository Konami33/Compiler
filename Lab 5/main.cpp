#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

map<char, vector<string>> productions;
// bool DEBUG = true;

// void debug_print(const string& msg, int indent = 0) {
//     if (DEBUG) {
//         for (int i = 0; i < indent; i++) cout << "  ";
//         cout << msg << endl;
//     }
// }

bool isNonTerminal(char symbol) {
    return productions.find(symbol) != productions.end();
}

bool parseString(const string& input, int& index, char nonTerminal, int depth = 0) {
    
    vector<string> prods = productions[nonTerminal];
    sort(prods.begin(), prods.end(), 
         [](const string& a, const string& b) { return a.length() < b.length(); });
    
    for (const string& production : prods) {
        
        int savedIndex = index;
        bool match = true;
        
        if (production == "e") {
            return true;
        }

        for (char symbol : production) {
            if (isNonTerminal(symbol)) {
                
                if (!parseString(input, index, symbol, depth + 1)) {
                    // Check if this non-terminal has epsilon production
                    bool hasEpsilon = false;
                    for (const string& p : productions[symbol]) {
                        if (p == "e") {
                            hasEpsilon = true;
                            break;
                        }
                    } 
                    if (hasEpsilon) {
                        continue;
                    }
                    match = false;
                    break;
                }
            } else {
                if (index >= input.size() || input[index] != symbol) {
                    match = false;
                    break;
                }
                index++;
            }
        }

        if (match) {  
            return true;
        }
        index = savedIndex;
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

    cout << "\nGrammar productions:" << endl;
    for (const auto& rule : productions) {
        cout << "Non-terminal: " << rule.first << endl;
        for (const string& prod : rule.second) {
            cout << "  -> " << prod << endl;
        }
    }

    int test;
    cin >> test;
    cin.ignore();
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