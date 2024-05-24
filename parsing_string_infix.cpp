#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


using namespace std;

bool Operator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%';
}

vector<string> elemen(const string& infix) {
    vector<string> elemens;
    string number;

    for (size_t i = 0; i < infix.size(); ++i) {
        char op = infix[i];

        if (isspace(op)) {
            continue;
        }

        if (isdigit(op)) {
            number += op;
        } else if (op == '-' && (i == 0 || Operator(infix[i - 1]) || infix[i - 1] == '(' || infix[i - 1] == ')')) {
            number += op;
        } else {
            if (!number.empty()) {
                elemens.push_back(number);
                number.clear();
            }

            elemens.push_back(string(1, op));
        }
    }

    if (!number.empty()) {
        elemens.push_back(number);
    }
    
    vector<string> prosesElemen;
    for (size_t i = 0; i < elemens.size(); ++i) {
        if (elemens[i] == "-" && (i == 0 || (Operator(elemens[i - 1][0]) && elemens[i - 1].size() == 1) || elemens[i - 1] == "(" || elemens[i - 1] == ")")) { 
            prosesElemen.push_back("-1");
            prosesElemen.push_back("*");
        } else {
            prosesElemen.push_back(elemens[i]);
        }
    }

    return prosesElemen;
}


void printElemen(const vector<string>& elemens) {
    for (size_t i = 0; i < elemens.size(); ++i) {
        if (i != 0) cout << " ";
        cout << elemens[i];
    }
    cout << endl;
}

int main() {

    string infix;
    getline(cin, infix);
    vector<string> elemens = elemen(infix);
    printElemen(elemens);

    return 0;
}