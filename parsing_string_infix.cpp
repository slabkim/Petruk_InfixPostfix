#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool isOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%';
}

int Precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

vector<string> stringToInfix(string str) {
    vector<string> infix;
    string angka;

    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];

        if (isspace(ch)) {
            continue;
        }
        else if (isdigit(ch) || ch == '.') {
            angka += ch;
        } 
        else if (ch == '-' && (i == 0 || isOperator(str[i - 1]))) {
            if(isOperator(str[i-1]) || str[i+1] == '('){
                infix.push_back("-1");
                infix.push_back("*");
            }
            else{
                angka += ch;
            }
        } 
        else {
            if (!angka.empty()) {
                infix.push_back(angka);
                angka.clear();
            }
            infix.push_back(string(1, ch));
        }
    }

    if (!angka.empty()) {
        infix.push_back(angka);
    }
    return infix;
}

vector<string> infixToPostfix(const vector<string>& infix) {
    vector<string> postfix;
    stack<string> ops;

    for (const string& token : infix) {
        if (isdigit(token[0]) || token[0] == '.' || (token.size() > 1 && (isdigit(token[1]) || token[1] == '.'))) {
            postfix.push_back(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                postfix.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        } else if (isOperator(token[0])) {
            while (!ops.empty() && Precedence(ops.top()[0]) >= Precedence(token[0])) {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        postfix.push_back(ops.top());
        ops.pop();
    }

    return postfix;
}

void printInfix(const vector<string>& infix) {
    for (size_t i = 0; i < infix.size(); ++i) {
        cout << infix[i] << " ";
    }
    cout << endl;
}



int main() {
    string str;
    getline(cin, str);

    vector<string> infix = stringToInfix(str);

    printInfix(infix);

    return 0;
}