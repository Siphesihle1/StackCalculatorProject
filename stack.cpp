#include "stack.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

void Stack::push(int value)
{
	data.push_back(value);
}

void Stack::pop()
{
	if (size()) {
		data.pop_back();
	} else {
		throw underflow_error("The stack is empty");
	}

}

int& Stack::peek()
{
	if (size()) {
		return data[size() - 1];
	} else {
		throw out_of_range("The stack is empty");
	}

}

size_t Stack::size() const
{
	return data.size();
}

void CharStack::push(char value)
{
	/*bool found = false;

	for (char i : c.data) {
		if (i == value) {
			found = true;
			break;
		}	
	}

	if (!found) {
		c.data.push_back(value);
	}*/

	data.push_back(value);
}

void CharStack::pop()
{
	if (size()) {
		data.pop_back();
	} else {
		throw underflow_error("The stack is empty");
	}
}

char& CharStack::peek()
{
	if (size()) {
		return data[size() - 1];
	} else {
		throw out_of_range("The stack is empty");
	}

}

size_t CharStack::size() const
{
	return data.size();
}

int precedence(char c)
{
	switch (c) {
		case '(':
		case ')': return 3;
		case '*':
		case '/': return 2;
		case '+':
		case '-': return 1;
		default:
			throw invalid_argument("Invalid operator");
	}
}

bool is_operator(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

int operate(int a, int b, char o) {
	switch(o) {
		case '+' :
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}
}

bool is_numeric(string s)
{

	for (char c : s) {
		//int a = c - '0';
		if (!(c >='0' && c <= '9')) {
			return false;
		}
	} 
	
	return true;
}


int calculate(string postfix)
{	
	int result = 0;

	Stack opd;

	for (char c : postfix) {
		string s (1, c);	
		if (is_numeric(s)) {
			int d = c - '0';
			opd.push(d);
		}

		if (is_operator(c)) {
			if (opd.size() > 1) {
				int b = opd.peek();
				opd.pop();
				int a = opd.peek();
				opd.pop();
	  			opd.push(operate(a, b, c));
			} else {
				throw ("Too few operands");
			}
		}
	}

	if (opd.size() > 1) {
		throw ("Malformed expression");
	} else {
		result = opd.peek();
		opd.pop();
		return result;
	}

}

string to_postfix(string infix)
{
	CharStack c_stack;
	string out = "";

	for (char t : infix) {
		string s (1, t);
		if (is_numeric(s)) {
			out += t;
		} else if (t == '(') {
			c_stack.push(t);
		} else if (is_operator(t)) {
			if (c_stack.size() == 0) {
				c_stack.push(t);
			} else {
				if (c_stack.peek() != '(') {
					while (c_stack.size() > 0 && (precedence(c_stack.peek()) > precedence(t))) {
						out += c_stack.peek();
						c_stack.pop();
					}
					c_stack.push(t);
				} else {
					c_stack.push(t);
				}
			}
					
		} else if (t == ')') {
			while (c_stack.size() > 0 && c_stack.peek() != '(') {
				out += c_stack.peek();
				c_stack.pop();
			}
			c_stack.pop();
		}
	}
	
	while (c_stack.size() > 0) {
		if (c_stack.peek() == '(') {
			throw ("Too many operands");
		} else {
			out += c_stack.peek();
			c_stack.pop();
	
		}
	}
	
	return out;
}

int calculate_extra(string postfix)
{
	Stack cpd;
	int result = 0;
	stringstream p(postfix);
	string post;


	while (p >> post) {
		if (is_numeric(post)) {
			int d = stoi(post);
			cpd.push(d);
		}

		char c = post[0];
		if (is_operator(c)) {
			if (cpd.size() > 1) {
				int b = cpd.peek();
				cpd.pop();
				int a = cpd.peek();
				cpd.pop();
	  			cpd.push(operate(a, b, c));
			} else {
				throw ("Too few operands");
			}
		}
	}



	/*if (cpd.size() != 1) {
		throw ("Malformed expression");
	} else {
		result = cpd.peek();
		cpd.pop();
		return result;
	}*/

	if (cpd.size() == 1) {
		result = cpd.peek();
		cpd.pop();
		return result;
	} else {
		throw ("Malformed expression");
	}
	
}

