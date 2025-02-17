#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <cctype>

using namespace std;

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
    }
    return 0;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0; // for any other operator
}

int evaluateExpression(string expression) {
    stack<int> values;
    stack<char> ops;
    vector<string> steps;
    string current_expression = expression; // to store the current expression

    // Print the initial expression
    cout << current_expression << endl;
    
    for (size_t i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0'); //handling multi-digit numbers
                i++;
            }
            i--; // Adjust for loop increment
            values.push(val);
        } 
        else if (expression[i] == '(') { // opening parenthesis
            ops.push(expression[i]);
        } 
        else if (expression[i] == ')') { // closing parenthesis
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                int result = applyOperation(val1, val2, op);
                values.push(result);

                // handling updating the expression
                string old_part = to_string(val1) + op + to_string(val2);
                string new_part = to_string(result);
                size_t pos = current_expression.find(old_part);
                if (pos != string::npos) {
                    current_expression.replace(pos, old_part.length(), new_part);
                    steps.push_back(current_expression);
                }
            }
            ops.pop(); // Remove '('
        } 
        else {
            // Handling operator precedence
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                int result = applyOperation(val1, val2, op);
                values.push(result);

                // Update expression with the computed result
                string old_part = to_string(val1) + op + to_string(val2);
                string new_part = to_string(result);
                size_t pos = current_expression.find(old_part);
                if (pos != string::npos) {
                    current_expression.replace(pos, old_part.length(), new_part);
                    steps.push_back(current_expression);
                }
            }
            ops.push(expression[i]);
        }
    }

    // Process remaining operators
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        int result = applyOperation(val1, val2, op);
        values.push(result);

        // handling updating the expression
        string old_part = to_string(val1) + op + to_string(val2);
        string new_part = to_string(result);
        size_t pos = current_expression.find(old_part);
        if (pos != string::npos) {
            current_expression.replace(pos, old_part.length(), new_part);
            steps.push_back(current_expression);
        }
    }

    // Print the result
    for (const auto& step : steps) {
        cout << step << endl;
    }
    return values.top();
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;

    int result = evaluateExpression(expression);
    cout << "Final result: " << result << endl;

    return 0;
}
