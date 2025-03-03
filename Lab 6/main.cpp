#include<bits/stdc++.h>

using namespace std;

map<pair<char, char>, char> transitions;
set<char> acceptingStates;
char startState;



int main() {
    int numTransitions;
    cin >> numTransitions;

    for (int i = 0; i < numTransitions; ++i) {
        char from, input, to;
        cin >> from >> input >> to;
        transitions[{from, input}] = to;
    }

    startState = 'a';
    acceptingStates.insert('c');

    int t;
    cin >> t;
    while(t--) {

        string inputString;
        cin >> inputString;

        char currentState = startState;
        for (char symbol : inputString) {
            auto transition = transitions.find({currentState, symbol});
            if (transition == transitions.end()) {
                return 0;
            }
            currentState = transition->second;
        }

        if (acceptingStates.find(currentState) != acceptingStates.end()) {
            cout << "Accepted" << endl;
        } else {
            cout << "Rejected" << endl;
        }
    }

    return 0;
}