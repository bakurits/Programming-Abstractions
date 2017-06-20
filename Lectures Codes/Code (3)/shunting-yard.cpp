/* File: shunting-yard.cpp
 *
 * An implementation of Dijkstra's shunting-yard algorithm for evaluating
 * infix expressions.
 */
 
#include <iostream>
#include <string>
#include "simpio.h"
#include "tokenscanner.h"
#include "stack.h"
#include "strlib.h"
using namespace std;

int evaluate(string expression);

int main() {
	while (true) {
		string line = getLine("Enter an expression: ");
		if (line == "") break;
		
		cout << "That evaluates to " << evaluate(line) << endl;
	}
	
	return 0;
}

/* Given an operator, returns a number encoding the precedence of that
 * operator.  Lower numbers indicate lower precedence.
 */
int precedenceOf(char op) {
	/* + and - have the lowest precedence. */
	if (op == '+' || op == '-') return 1;
	
	/* We assume everything else would be either * or /, which
	 * have a higher precedence.
	 */
	else return 2;
}

/* Given the stack of operands and stack of operators,
 * evaluates one operator as applied to two operands.
 */
void evaluateOneOperator(Stack<int>& operands,
                         Stack<char>& operators) {
	/* Determine which operator to use.  This is the top operator
	 * on the operator stack.
	 */
	char op = operators.pop();
	
	/* Obtain the lhs and rhs of the operation, which are stored
	 * in reverse order on the stack.
	 */
	int rhs = operands.pop();
	int lhs = operands.pop();
	
	/* Evaluate the operator. */
	if (op == '+') operands.push(lhs + rhs);
	if (op == '-') operands.push(lhs - rhs);
	if (op == '*') operands.push(lhs * rhs);
	if (op == '/') operands.push(lhs / rhs);
}

/* Given a string representation of a mathematical expression,
 * evaluates that expression.
 */
int evaluate(string expression) {
	/* Set up a scanner to tokenize the expression, then have it
	 * discard all whitespace (which we don't use.)
	 */
	TokenScanner scanner(expression);
	scanner.ignoreWhitespace();
	
	/* Track a stack of operands and a stack of operators. */
	Stack<int> operands;
	Stack<char> operators;
	
	/* Process all tokens until we've looked at everything. */
	while (scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		
		/* If we read a number, put it atop the operands stack. */
		if (scanner.getTokenType(token) == NUMBER) {
			operands.push(stringToInteger(token));
		}
		/* We assume everything else is an operator. */
		else {
			char op = token[0];
			
			/* Keep processing operators from the operator stack until
			 * this new operator has higher precedence than the current
			 * operator.
			 */
			while (!operators.isEmpty() &&
			       precedenceOf(op) <= precedenceOf(operators.top())) {
			 	evaluateOneOperator(operands, operators);      
			}
			
			operators.push(op);
		}
	}
	
	/* Now that we've seen all tokens, evaluate all remaining operators. */
	while (!operators.isEmpty()) {
		evaluateOneOperator(operands, operators);  
	}

	return operands.pop();
}



