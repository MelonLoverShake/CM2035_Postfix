#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Interpreter.h"

using namespace std;

const int MAX_TOKENS = 100; // Define a maximum number of tokens

// Convert user input line to tokens and store them in a fixed-size array
void userInput(const string& line, string tokens[], int& tokenCount) {
    stringstream ss(line);
    string token;
    tokenCount = 0;
    while (ss >> token && tokenCount < MAX_TOKENS) {
        tokens[tokenCount++] = token;
    }
}

int main() {
    Interpreter interpreter;
    string line;
    string tokens[MAX_TOKENS];
    int tokenCount;

    cout << "Enter variable assignments (e.g., A 3 =). Type 'end' to finish:" << endl;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line == "end") break;

        userInput(line, tokens, tokenCount);
        if (tokenCount == 3 && tokens[2] == "=") {
            char varName = tokens[0][0];
            double varValue = stod(tokens[1]);
            interpreter.assignVariable(varName, varValue);
            interpreter.symbolTable.print();
        } else {
            cout << "Invalid input format for variable assignment." << endl;
        }
    }

    cout << "Enter the postfix expression:" << endl;
    cout << "> ";
    getline(cin, line);
    userInput(line, tokens, tokenCount);

    try {
        interpreter.run(tokens, tokenCount);
cout << "The result is: " << interpreter.getResult() << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
