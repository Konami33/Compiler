Let’s walk through the code step-by-step with an example input string `aaabb` and the following CFG rules:

### CFG Rules:
```
3
S AB
A aA a
B bB b
```

This CFG can generate strings like `ab`, `aab`, `aaabb`, etc. Here's how the code processes the input string `aaabb`:

---

### Step-by-Step Walkthrough

#### 1. **Input CFG Rules**
The CFG rules are read and stored in the `productions` map as follows:
```cpp
productions = {
    'S': ["AB"],
    'A': ["aA", "a"],
    'B': ["bB", "b"]
};
```

#### 2. **Input String**
The input string to parse is `aaabb`.

#### 3. **Start Parsing**
The parsing begins with the start symbol `'S'` and the initial index `0`:
```cpp
int index = 0;
bool accepted = parseString(input, index, 'S');
```

#### 4. **Parsing `'S'`**
- The parser looks up the productions for `'S'` and finds `["AB"]`.
- It tries to match the production `"AB"`:
  - It recursively parses `'A'` and then `'B'`.

#### 5. **Parsing `'A'`**
- The parser looks up the productions for `'A'` and finds `["aA", "a"]`.
- It tries the first production `"aA"`:
  - It matches the terminal `'a'` with the input at index `0` (`input[0] = 'a'`). The index is incremented to `1`.
  - It recursively parses `'A'` again at index `1`.

#### 6. **Parsing `'A'` Again**
- The parser again looks up the productions for `'A'` and tries `"aA"`:
  - It matches the terminal `'a'` with the input at index `1` (`input[1] = 'a'`). The index is incremented to `2`.
  - It recursively parses `'A'` again at index `2`.

#### 7. **Parsing `'A'` One More Time**
- The parser again looks up the productions for `'A'` and tries `"aA"`:
  - It matches the terminal `'a'` with the input at index `2` (`input[2] = 'a'`). The index is incremented to `3`.
  - It recursively parses `'A'` again at index `3`.

#### 8. **Parsing `'A'` for the Last Time**
- The parser again looks up the productions for `'A'` and tries `"aA"`:
  - It cannot match the terminal `'a'` with the input at index `3` (`input[3] = 'b'`). This production fails.
- It backtracks and tries the second production `"a"`:
  - It matches the terminal `'a'` with the input at index `3` (`input[3] = 'b'`). This production also fails.
- Since no production for `'A'` matches, the parser backtracks to the previous call.

#### 9. **Backtracking to `'A'`**
- The parser backtracks to the previous call for `'A'` at index `2`:
  - It tries the second production `"a"`:
    - It matches the terminal `'a'` with the input at index `2` (`input[2] = 'a'`). The index is incremented to `3`.
    - This production succeeds, and the parser returns to the previous call.

#### 10. **Parsing `'B'`**
- The parser now parses `'B'` at index `3`:
  - It looks up the productions for `'B'` and finds `["bB", "b"]`.
  - It tries the first production `"bB"`:
    - It matches the terminal `'b'` with the input at index `3` (`input[3] = 'b'`). The index is incremented to `4`.
    - It recursively parses `'B'` again at index `4`.

#### 11. **Parsing `'B'` Again**
- The parser again looks up the productions for `'B'` and tries `"bB"`:
  - It matches the terminal `'b'` with the input at index `4` (`input[4] = 'b'`). The index is incremented to `5`.
  - It recursively parses `'B'` again at index `5`.

#### 12. **Parsing `'B'` for the Last Time**
- The parser again looks up the productions for `'B'` and tries `"bB"`:
  - It cannot match the terminal `'b'` with the input at index `5` (end of input). This production fails.
- It backtracks and tries the second production `"b"`:
  - It matches the terminal `'b'` with the input at index `4` (`input[4] = 'b'`). The index is incremented to `5`.
  - This production succeeds, and the parser returns to the previous call.

#### 13. **Final Check**
- The parser checks if the entire input string has been consumed (`index == input.size()`).
- Since `index = 5` and `input.size() = 5`, the input string is fully consumed.
- The parser returns `true`, indicating that the input string `aaabb` is accepted by the CFG.

---

### Output
```
Input string "aaabb" is ACCEPTED by the CFG.
```

---

### Summary of Steps
1. The parser starts with `'S'` and tries to match `"AB"`.
2. It recursively parses `'A'` and matches `"aA"` three times, consuming `aaa`.
3. It backtracks and matches `"a"` for the last `'A'`, consuming `a`.
4. It then parses `'B'` and matches `"bB"` once, consuming `b`.
5. It backtracks and matches `"b"` for the last `'B'`, consuming `b`.
6. The entire input string `aaabb` is consumed, and the parser accepts it.

This walkthrough demonstrates how the recursive descent parser works step-by-step to match the input string with the CFG rules. Let me know if you have further questions!



```c++
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

map<char, vector<string>> productions;
bool DEBUG = true;

void debug_print(const string& msg, int indent = 0) {
    if (DEBUG) {
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << msg << endl;
    }
}

bool isNonTerminal(char symbol) {
    return productions.find(symbol) != productions.end();
}

bool parseString(const string& input, int& index, char nonTerminal, int depth = 0) {
    // debug_print("Trying to parse " + string(1, nonTerminal) + " at index " + to_string(index), depth);
    

    vector<string> prods = productions[nonTerminal];
    sort(prods.begin(), prods.end(), 
         [](const string& a, const string& b) { return a.length() < b.length(); });
    
    for (const string& production : prods) {
        // debug_print("Trying production " + string(1, nonTerminal) + " -> " + production, depth);
        
        int savedIndex = index;
        bool match = true;
        
        // Handle epsilon production
        if (production == "e") {
            // debug_print("Epsilon production found - success without consuming input", depth);
            return true;
        }

        for (char symbol : production) {
            if (isNonTerminal(symbol)) {
                //debug_print("Processing non-terminal " + string(1, symbol), depth);
                
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
                        // debug_print("Non-terminal " + string(1, symbol) + " can be epsilon", depth);
                        continue;
                    }
                    
                    match = false;
                    // debug_print("Failed to match non-terminal " + string(1, symbol), depth);
                    break;
                }
            } else {
                if (index >= input.size() || input[index] != symbol) {
                    match = false;
                    // debug_print("Failed to match terminal " + string(1, symbol) + " at index " + to_string(index), depth);
                    break;
                }
                // debug_print("Matched terminal " + string(1, symbol) + " at index " + to_string(index), depth);
                index++;
            }
        }

        if (match) {
            // debug_print("Successfully matched production " + string(1, nonTerminal) + " -> " + production, depth);
            return true;
        }

        // debug_print("Backtracking: resetting index from " + to_string(index) + " to " + to_string(savedIndex), depth);
        index = savedIndex;
    }

    // debug_print("Failed to match any production for " + string(1, nonTerminal), depth);
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
```