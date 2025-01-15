#include<bits/stdc++.h>
using namespace std;

vector <string> dataTypes = {"int", "float", "double", "char", "string", "bool"};
vector <string > keywords = {"for", "while", "if", "else", "return", "break", "continue", "cin", "cout", "endl"};
vector <string> operators = {"+", "-", "*", "/", "%", "++", "--", "+=", "-=", "*=", "/=", "%=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!"};
vector <string> punctuators = {",", ";", "(", ")", "{", "}", "[", "]"};

vector <string> dataTypesFound, keywordsFound, operatorsFound, punctuatorsFound, digitsFound;
unordered_set <string> identifiersFound;

void printVector(vector <string> v, string type) {
    cout << "<" << type << " : ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << ">" <<endl;
}

void printSet(unordered_set <string> s, string type) {
    cout << "<" << type << " : ";
    for (auto i = s.begin(); i != s.end(); i++) {
        cout << *i << " ";
    }
    cout << " >" <<endl;
}


void verifyToken(string token) {
    if(find(dataTypes.begin(), dataTypes.end(), token) != dataTypes.end()) {
        dataTypesFound.push_back(token);
    }
    else if(find(keywords.begin(), keywords.end(), token) != keywords.end()) {
        keywordsFound.push_back(token);
    }
    else if(find(operators.begin(), operators.end(), token) != operators.end()) {
        operatorsFound.push_back(token);
    }
    else if(find(punctuators.begin(), punctuators.end(), token) != punctuators.end()) {
        punctuatorsFound.push_back(token);
    }
    else if(isdigit(token[0])) {
        int countPoint = 0;
        for (int i = 0; i < token.size(); i++) {
            if(token[i] == '.') {
                countPoint++;
            }
            if(countPoint > 1) {
                cout << "Invalid number: " << token << endl;
                break;
            }
        }

        if (countPoint < 2) digitsFound.push_back(token);
    }
    else {
        identifiersFound.insert(token);
    }
}

void tokenize(string input) {
    string s = "";
    int i = 0;
    while(i<input.size()) {
        // first check for any spaces
        if(input[i] == ' ') {
            i++;
            continue;
        }
        // check for operators
        else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '%') {
            s.clear();
            while( i < input.size() && input[i] != ' ' && input[i] != ';' && input[i] != '\n' && (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '%')) {
                s += input[i];
                i++;
            }
            verifyToken(s);
        }
        // check for identifers
        else if (isalpha(input[i]) || input[i] == '_') {
            s.clear();
            while( i < input.size() && input[i] != ' ' && input[i] != ',' && input[i] != ';' && input[i] != '\n' && (isalnum(input[i]) || input[i] == '_') || isalpha(input[i])) {
                s += input[i];
                i++;
            }
            verifyToken(s);
        }
        // check for numbers
        else if (isdigit(input[i])) {
            s.clear();
            while( i < input.size() && input[i] != ' ' && input[i] != ';' && input[i] != ',' && input[i] != '\n' && (isdigit(input[i]) || input[i] == '.')) {
                s += input[i];
                i++;
            }
            // cout << "Number found from: " << s << endl;
            verifyToken(s);
        }
        else {
            s.clear();
            s += input[i];
            i++;
            verifyToken(s);
        }

    }
}

int main() {
    string input = R"(
        int x,y;
        for(int i=0;i<10.0;i++) {
            cin>>x>>y;
            cout<<x+y<<endl;
        }
        return 0;
    )";
    tokenize(input);
    printVector(dataTypesFound, "Data Types");
    printVector(keywordsFound, "Keywords");
    printVector(operatorsFound, "Operators");
    printVector(punctuatorsFound, "Punctuators");
    printSet(identifiersFound, "Identifiers");
    printVector(digitsFound, "Digits");
    return 0;
}