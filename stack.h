#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>

using std::vector;
using std::size_t;
using std::string;

class Stack
{
public:
    void push(int value);
    void pop();
    int& peek();
    size_t size() const;
protected:
    vector<int> data;
};

class CharStack
{
public:
    void push(char value);
    void pop();
    char& peek();
    size_t size() const;
protected:
    vector<char> data;
};

int precedence(char c);
bool is_operator(char c);
bool is_numeric(string s);
int calculate(string postfix);
string to_postfix(string infix);
int calculate_extra(string postfix);

#endif // STACK_H
