#include<bits/stdc++.h>

using namespace std;

// const set<char>& states, const set<char>& symbols,

bool simulateNFA(char initialState, const set<char>& finalStates, const map<pair<char, char>, set<char>>& transitions, const string& input) {
    
    set<char> currentStates = {initialState};

    for (char ch : input) {
        set<char> nextStates;
        for (char state : currentStates) {
            auto key = make_pair(state, ch);
            if (transitions.find(key) != transitions.end()) {
                nextStates.insert(transitions.at(key).begin(), transitions.at(key).end());
            }
        }
        currentStates = nextStates;
        if (currentStates.empty()) {
            break;
        }
    }

    // Check if any of the current states is a final state
    for (char state : currentStates) {
        if (finalStates.find(state) != finalStates.end()) {
            return true;
        }
    }
    return false;
}

int main() {

    // Input: Initial State
    char initialState;
    cout << "Enter the initial state: ";
    cin >> initialState;

    // Input: Final States
    set<char> finalStates;
    cout << "Enter the number of final states: ";
    int numFinalStates;
    cin >> numFinalStates;
    cout << "Enter the final states: ";
    for (int i = 0; i < numFinalStates; ++i) {
        char finalState;
        cin >> finalState;
        finalStates.insert(finalState);
    }

    // Input: Transitions
    map<pair<char, char>, set<char>> transitions; // (state, symbol) -> { next states }
    cout << "Enter the number of transitions: ";
    int numTransitions;
    cin >> numTransitions;
    cout << "Enter the transitions in the format: state symbol next_state1 next_state2 ...\n";
    for (int i = 0; i < numTransitions; ++i) {
        char state;
        char symbol;
        cin >> state >> symbol;
        set<char> nextStates;
        char nextState;
        while (cin >> nextState) {
            nextStates.insert(nextState);
            if (cin.peek() == '\n') break;
        }
        transitions[make_pair(state, symbol)] = nextStates;
    }

    // Input: String to validate
    string input;
    cout << "Enter the string to validate: ";
    cin >> input;

    // Simulate the NFA
    bool isAccepted = simulateNFA(initialState, finalStates, transitions, input);

    // Output the result
    if (isAccepted) {
        cout << "The string is accepted by the NFA.\n";
    } else {
        cout << "The string is not accepted by the NFA.\n";
    }

    return 0;
}