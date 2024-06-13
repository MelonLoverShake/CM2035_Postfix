#include "Interpreter.h"
#include <cmath>
#include <stdexcept>
#include <cctype>

Interpreter::Interpreter() : stackTop(-1) {}

double Interpreter::stackPop() {
    if (stackTop < 0) {
        throw std::runtime_error("stack is empty");
    }
    return stack[stackTop--];
}

double Interpreter::resolve(double value) {
    return value;
}

double Interpreter::resolve(char var) {
    return symbolTable.search(var);
}

void Interpreter::add() {
    double right = resolve(stackPop());
    double left = resolve(stackPop());
    stack[++stackTop] = left + right;
}

void Interpreter::multiply() {
    double right = resolve(stackPop());
    double left = resolve(stackPop());
    stack[++stackTop] = left * right;
}

void Interpreter::subtract() {
    double right = resolve(stackPop());
    double left = resolve(stackPop());
    stack[++stackTop] = left - right;
}

void Interpreter::divide() {
    double right = resolve(stackPop());
    double left = resolve(stackPop());
    if (right == 0) {
        throw std::runtime_error("division by zero");
    }
    stack[++stackTop] = left / right;
}

void Interpreter::modulo() {
    double right = resolve(stackPop());
    double left = resolve(stackPop());
    stack[++stackTop] = fmod(left, right);
}

void Interpreter::round() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::round(value);
}

void Interpreter::floor() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::floor(value);
}

void Interpreter::ceil() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::ceil(value);
}

void Interpreter::abs() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::fabs(value);
}

void Interpreter::cos() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::cos(value);
}

void Interpreter::sin() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::sin(value);
}

void Interpreter::tan() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::tan(value);
}

void Interpreter::log10() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::log10(value);
}

void Interpreter::log2() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::log2(value);
}

void Interpreter::exp() {
    double value = resolve(stackPop());
    stack[++stackTop] = ::exp(value);
}

void Interpreter::factorial() {
    double value = resolve(stackPop());
    stack[++stackTop] = calculateFactorial(value);
}

void Interpreter::cot() {
    double value = resolve(stackPop());
    double sinValue = std::sin(value);
    if (sinValue == 0) {
        throw std::runtime_error("Cotangent is undefined for sin(x) = 0");
    }
    stack[++stackTop] = std::cos(value) / sinValue;
}

double Interpreter::calculateFactorial(double n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * calculateFactorial(n - 1);
    }
}

void Interpreter::max() {
    if (stackTop < 1) {
        throw std::runtime_error("Error: Not enough elements in the stack to perform max operation.");
    }

    double right = resolve(stackPop());
    double left = resolve(stackPop());

    double maximum = std::max(left, right);

    stack[++stackTop] = maximum;
}

void Interpreter::min() {
    if (stackTop < 1) {
        throw std::runtime_error("Error: Not enough elements in the stack to perform min operation.");
    }

    double right = resolve(stackPop());
    double left = resolve(stackPop());

    double minimum = std::min(left, right);

    stack[++stackTop] = minimum;
}

void Interpreter::run(const std::string tokens[], int tokenCount) {
    for (int i = 0; i < tokenCount; ++i) {
        const std::string& token = tokens[i];

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            stack[++stackTop] = std::stod(token);
        } else if (token.size() == 1 && isalpha(token[0])) {
            stack[++stackTop] = resolve(token[0]);
        } else {
            if (token == "+") add();
            else if (token == "*") multiply();
            else if (token == "-") subtract();
            else if (token == "/") divide();
            else if (token == "%") modulo();
            else if (token == "round") round();
            else if (token == "floor") floor();
            else if (token == "ceil") ceil();
            else if (token == "abs") abs();
            else if (token == "cos") cos();
            else if (token == "sin") sin();
            else if (token == "tan") tan();
            else if (token == "log10") log10();
            else if (token == "log2") log2();
            else if (token == "exp") exp();
            else if (token == "!") factorial();
            else if (token == "cot") cot();
            else if (token == "max") max();
            else if (token == "min") min();
            else {
                throw std::runtime_error("Unknown operator: " + token);
            }
        }
    }
    if (stackTop != 0) {
        throw std::runtime_error("stack length is " + std::to_string(stackTop + 1));
    }
}

double Interpreter::getResult() {
    if (stackTop < 0) {
        throw std::runtime_error("stack is empty");
    }
    return stack[stackTop];
}

void Interpreter::assignVariable(char varName, double varValue) {
    symbolTable.insert(varName, varValue);
}
