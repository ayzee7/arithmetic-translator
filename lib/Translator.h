#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <exception>
#include "Stack.h"

using namespace std;

class Translator {

	enum {
		STATE_INIT,
		STATE_OPERAND,
		STATE_ERROR,
		STATE_NUM_DOUBLE,
		STATE_VAR,
		STATE_NUM_INT
	} STATES;

	string user_input;
	vector<pair<string, int>> int_variables;		//	Container for initialized integer variables
	vector<pair<string, double>> double_variables;		//	Container for initialized floating point variables

	double assignment(string var_name, string var_value, bool is_test);		//	Performs assignment for variables

	double output_result(string expr, bool is_test);		//	Calculates arithmetic expression and outputs result

	void lvalue_analysis(string lvalue);		//	Variable name analysis

	void expression_analysis(string expr);		//	Expression syntax analysis

	string compute_value(string expr);		//	Expression value computation

	vector<string> get_terms(string expr);		//	Expression lexical analysis and splits expression into tokens

	int priority(string term);		//	Returns priority of arithmetic sign

	bool check_variable_term(string term);		//	Checks if a variable is initialized

public:
	void execute();

	double test_execute(string input);		//	Performs operations with given string
};