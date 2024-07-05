
#include "HashTable.h"
#include <string>

class Interpreter {
private:
    static const int STACK_MAX_SIZE = 100;
    double stack[STACK_MAX_SIZE];
    int stackTop;
    

    double stackPop();
    double resolve(double value);
    double resolve(char var);

    void add();
    void multiply();
    void subtract();
    void divide();
    void modulo();
    void round();
    void floor();
    void ceil();
    void abs();
    void cos();
    void sin();
    void tan();
    void log10();
    void log2();
    void exp();
    void factorial();
    void cot();
    void max();
    void min();

    double calculateFactorial(double n);

public:
    Interpreter();
    void run(const std::string tokens[], int tokenCount);
    double getResult();
    double peek() const;
    void assignVariable(char varName, double varValue);
    HashTable symbolTable;
};



